/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/tool/node_selection_tool.h"

#include "flow/document/command/change_node.h"
#include "flow/document/component/scene/item/node_item.h"
#include "flow/document/component/scene/item/selection_rectangle.h"
#include "flow/document/component/scene/scene.h"
#include "flow/document/document.h"
#include "flow/document/flow/group_layer.h"
#include "flow/document/flow/node_layer.h"
#include "flow/document/resources.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/command/group_command.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------------- isMoveable ------------------------------ */

namespace {

[[nodiscard]] bool isMoveable(Node *node) {
  auto layer = static_cast<Layer *>(node->getParent());
  do {
    if (layer->isLocked()) return false;
  } while (layer = layer->getParent());

  return true;
}

}  // namespace

/* ---------------------------- NodeSelectionTool --------------------------- */

NodeSelectionTool::NodeSelectionTool(QObject *parent)
    : Tool(tr("Node Selection Tool"), QIcon(icons::x32::SelectionTool),
           QKeySequence(Qt::Key_S), parent),
      m_action(Action::NoAction),
      m_mouse_clicked_button(Qt::MouseButton{}),
      m_selection_rect(std::make_unique<SelectionRectangle>()),
      m_clicked_item(nullptr) {}

NodeSelectionTool::~NodeSelectionTool() = default;

void NodeSelectionTool::activate(FlowScene *scene) { Tool::activate(scene); }

void NodeSelectionTool::deactivate() { Tool::deactivate(); }

void NodeSelectionTool::keyPressEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void NodeSelectionTool::keyReleaseEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void NodeSelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event) {
  Tool::mouseMoved(event);

  const auto mouse_pos = event->scenePos();
  updateHover(mouse_pos);

  if (m_action == Action::NoAction &&
      m_mouse_clicked_button == Qt::LeftButton) {
    auto drag_distance = (m_mouse_clicked_pos - mouse_pos).manhattanLength();
    if (drag_distance >= QApplication::startDragDistance() / 2.0) {
      const auto any_item_selected = isAnyNodeSelected();

      if (m_clicked_item ||
          ((m_modifiers & Qt::AltModifier) && any_item_selected) &&
              !(m_modifiers & Qt::ShiftModifier)) {
        startItemMoving();
      } else if (m_modifiers & Qt::ShiftModifier) {
        startItemSelection();
      }
    }
  }

  switch (m_action) {
    case Action::ItemMoving:
      updateItemMoving(mouse_pos);
      break;

    case Action::ItemSelection:
      updateItemSelection(mouse_pos);
      break;

    default:
      break;
  }

  refreshCursor();
}

void NodeSelectionTool::mousePressed(QGraphicsSceneMouseEvent *event) {
  Tool::mousePressed(event);

  if (m_action != Action::NoAction) return;

  switch (event->button()) {
    case Qt::LeftButton: {
      m_mouse_clicked_button = Qt::LeftButton;
      m_mouse_clicked_pos = event->scenePos();

      if (auto scene = getScene(); scene) {
        auto item = scene->itemAt(m_mouse_clicked_pos, QTransform{});
        auto node_item = dynamic_cast<NodeItem *>(item);

        if (node_item) {
          auto node = node_item->getNode();
          if (isMoveable(node)) m_clicked_item = node_item;
        }
      }

      break;
    }

    default:
      break;
  }
}

void NodeSelectionTool::mouseReleased(QGraphicsSceneMouseEvent *event) {
  Tool::mouseReleased(event);

  switch (m_action) {
    case Action::ItemMoving:
      endItemMoving();
      break;

    case Action::ItemSelection:
      endItemSelection();
      break;

    case Action::NoAction: {
      if (m_clicked_item) {
        auto node = m_clicked_item->getNode();
        auto document = getDocument();

        document->setCurrentNode(node);

        if (m_modifiers & Qt::ControlModifier) {
          const auto &nodes = document->getSelectedNodes();
          if (nodes.contains(node)) {
            unselectNodes({m_clicked_item});
          } else {
            selectNodes({m_clicked_item});
          }
        } else {
          selectNodes({m_clicked_item}, false);
        }
      } else if (!(m_modifiers & (Qt::AltModifier | Qt::ControlModifier)) &&
                 event->button() == Qt::LeftButton) {
        selectNodes({}, false);
      }
      break;
    }
  }

  m_action = Action::NoAction;
  m_mouse_clicked_pos = QPointF{};
  m_mouse_clicked_button = Qt::MouseButton{};
  m_clicked_item = nullptr;

  refreshCursor();
}

void NodeSelectionTool::updateHover(const QPointF &mouse_pos) {
  if (auto scene = getScene(); scene) {
    auto item = scene->itemAt(mouse_pos, QTransform{});
    auto nodes = getNodes({item});
    nodes.removeIf([](auto node) { return !isMoveable(node); });

    getDocument()->setHoveredNodes(nodes);
  }
}

void NodeSelectionTool::startItemMoving() {
  m_action = Action::ItemMoving;

  if (m_clicked_item && !(m_modifiers & Qt::AltModifier)) {
    selectNodes({m_clicked_item}, false);
  }

  for (auto node : getDocument()->getSelectedNodes()) {
    if (isMoveable(node)) {
      m_moving_nodes.append(std::make_pair(node, node->getPosition()));
    }
  }
}

void NodeSelectionTool::startItemSelection() {
  m_action = Action::ItemSelection;
  if (auto scene = getScene(); scene) scene->addItem(m_selection_rect.get());
}

void NodeSelectionTool::updateItemMoving(const QPointF &mouse_pos) {
  if (m_moving_nodes.empty()) return;

  auto difference = mouse_pos - m_mouse_clicked_pos;
  auto group_move_command = new pillar::GroupCommand(tr("Move nodes"));

  for (auto &[moving_node, old_position] : m_moving_nodes) {
    auto new_position = old_position + difference;
    group_move_command->addCommand(
        new SetNodesPosition(getDocument(), {moving_node}, new_position));
  }

  getDocument()->getUndoStack()->push(group_move_command);
}

void NodeSelectionTool::updateItemSelection(const QPointF &mouse_pos) {
  auto scene = getScene();
  auto document = getDocument();

  if (scene && document) {
    m_selection_rect->setRect(
        QRectF(m_mouse_clicked_pos, mouse_pos).normalized());

    auto selected_items = scene->items(m_selection_rect->boundingRect());
    selectNodes(selected_items, false);
  }
}

void NodeSelectionTool::endItemMoving() { m_moving_nodes.clear(); }

void NodeSelectionTool::endItemSelection() {
  if (auto scene = getScene()) scene->removeItem(m_selection_rect.get());
}

void NodeSelectionTool::refreshCursor() {
  Qt::CursorShape cursor_shape = Qt::ArrowCursor;

  switch (m_action) {
    case Action::NoAction: {
      const auto any_item_selected = isAnyNodeSelected();
      const auto any_item_hovered = isAnyNodeHovered();

      if (any_item_hovered ||
          ((m_modifiers & Qt::AltModifier) && any_item_selected &&
           !(m_modifiers & Qt::ShiftModifier))) {
        cursor_shape = Qt::SizeAllCursor;
      }

      break;
    }

    case Action::ItemMoving:
      cursor_shape = Qt::SizeAllCursor;
      break;

    default:
      break;
  }

  setCursor(cursor_shape);
}

void NodeSelectionTool::selectNodes(const QList<QGraphicsItem *> items,
                                    bool extend) {
  auto document = getDocument();
  Q_ASSERT(document);

  auto nodes = getNodes(items);
  if (extend) nodes << document->getSelectedNodes();

  nodes.removeIf([](auto node) { return !isMoveable(node); });
  document->setSelectedNodes(nodes);
}

void NodeSelectionTool::unselectNodes(const QList<QGraphicsItem *> items) {
  auto document = getDocument();
  Q_ASSERT(document);

  auto nodes = document->getSelectedNodes();
  const auto nodes_to_unselect = getNodes(items);

  for (auto node_to_unselect : nodes_to_unselect)
    nodes.removeAll(node_to_unselect);

  nodes.removeIf([](auto node) { return !isMoveable(node); });
  document->setSelectedNodes(nodes);
}

QList<Node *> NodeSelectionTool::getNodes(
    const QList<QGraphicsItem *> items) const {
  auto nodes = QList<Node *>{};
  for (auto item : items) {
    if (auto node_item = dynamic_cast<NodeItem *>(item); node_item)
      nodes.append(node_item->getNode());
  }

  return nodes;
}

bool NodeSelectionTool::isAnyNodeSelected() const {
  return getDocument() != nullptr && !getDocument()->getSelectedNodes().empty();
}

bool NodeSelectionTool::isAnyNodeHovered() const { return false; }

}  // namespace flow