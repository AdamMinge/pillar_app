/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/selection_tool.h"

#include "flow_document/command/factory/object_command_factory.h"
#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/item/object_graphics_item.h"
#include "flow_document/component/scene/item/selection_rectangle.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/command/group_command.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

SelectionTool::SelectionTool(QObject *parent)
    : AbstractTool(tr("Selection Tool"), QIcon(icons::x32::SelectionTool),
                   QKeySequence(Qt::Key_S), parent),
      m_action(Action::NoAction),
      m_mouse_clicked_button(Qt::MouseButton{}),
      m_selection_rect(std::make_unique<SelectionRectangle>()),
      m_clicked_item(nullptr) {}

SelectionTool::~SelectionTool() = default;

void SelectionTool::activate(FlowScene *scene) {
  AbstractTool::activate(scene);
}

void SelectionTool::deactivate() { AbstractTool::deactivate(); }

void SelectionTool::keyPressEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void SelectionTool::keyReleaseEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void SelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event) {
  AbstractTool::mouseMoved(event);

  const auto mouse_pos = event->scenePos();
  updateHover(mouse_pos);

  if (m_action == Action::NoAction &&
      m_mouse_clicked_button == Qt::LeftButton) {
    auto drag_distance = (m_mouse_clicked_pos - mouse_pos).manhattanLength();
    if (drag_distance >= QApplication::startDragDistance() / 2.0) {
      const auto any_item_selected =
          getScene() != nullptr && !getScene()->selectedItems().empty();

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

void SelectionTool::mousePressed(QGraphicsSceneMouseEvent *event) {
  AbstractTool::mousePressed(event);

  if (m_action != Action::NoAction) return;

  switch (event->button()) {
    case Qt::LeftButton: {
      m_mouse_clicked_button = Qt::LeftButton;
      m_mouse_clicked_pos = event->scenePos();

      if (getScene()) {
        auto item = getScene()->itemAt(m_mouse_clicked_pos, QTransform{});

        auto flow_item = dynamic_cast<ObjectGraphicsItem *>(item);
        auto is_selectable =
            flow_item && flow_item->flags() & QGraphicsItem::ItemIsSelectable;

        if (flow_item && is_selectable) m_clicked_item = flow_item;
      }

      break;
    }

    default:
      break;
  }
}

void SelectionTool::mouseReleased(QGraphicsSceneMouseEvent *event) {
  AbstractTool::mouseReleased(event);

  switch (m_action) {
    case Action::ItemMoving:
      endItemMoving();
      break;

    case Action::ItemSelection:
      endItemSelection();
      break;

    case Action::NoAction: {
      if (m_clicked_item) {
        if (m_modifiers & Qt::ControlModifier) {
          m_clicked_item->setSelected(!m_clicked_item->isSelected());
        } else {
          getScene()->clearSelection();
          m_clicked_item->setSelected(true);
        }
      } else if (!(m_modifiers & (Qt::AltModifier | Qt::ControlModifier))) {
        getScene()->clearSelection();
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

void SelectionTool::updateHover(const QPointF &mouse_pos) {
  if (getScene()) {
    auto path = QPainterPath{};
    path.addEllipse(mouse_pos, 1, 1);
    getScene()->setHoveredArea(path);
  }
}

void SelectionTool::startItemMoving() {
  m_action = Action::ItemMoving;
  if (getScene()) {
    if (m_clicked_item && !(m_modifiers & Qt::AltModifier)) {
      getScene()->clearSelection();
      m_clicked_item->setSelected(true);
    }

    for (auto item : getScene()->selectedItems()) {
      if (auto flow_item = dynamic_cast<ObjectGraphicsItem *>(item); flow_item)
        m_moving_items.append(std::make_pair(flow_item, flow_item->pos()));
    }
  }
}

void SelectionTool::startItemSelection() {
  m_action = Action::ItemSelection;
  if (getScene()) getScene()->addItem(m_selection_rect.get());
}

void SelectionTool::updateItemMoving(const QPointF &mouse_pos) {
  QPointF difference = mouse_pos - m_mouse_clicked_pos;

  for (auto [selected_item, old_pos] : m_moving_items)
    selected_item->setPos(old_pos + difference);
}

void SelectionTool::updateItemSelection(const QPointF &mouse_pos) {
  if (getScene()) {
    m_selection_rect->setRect(
        QRectF(m_mouse_clicked_pos, mouse_pos).normalized());

    auto prev_selected_items = QList<QGraphicsItem *>{};
    if (m_modifiers & Qt::ControlModifier)
      prev_selected_items = getScene()->selectedItems();

    QPainterPath path;
    path.addRect(m_selection_rect->boundingRect());
    getScene()->setSelectionArea(path);

    for (auto prev_selected_item : prev_selected_items)
      prev_selected_item->setSelected(true);
  }
}

void SelectionTool::endItemMoving() {
  auto &[first_item, first_item_old_pos] = m_moving_items.front();
  auto move = first_item->pos() - first_item_old_pos;

  auto group_move_command = new egnite::GroupCommand(tr("Move objects"));
  for (auto &[moving_item, _] : m_moving_items) {
    auto object = moving_item->getObject();
    auto new_position = object->getPosition() + move;

    auto command_factory = getObjectCommandFactoryByObject(object);
    Q_ASSERT(command_factory);

    group_move_command->addCommand(command_factory->createSetPosition(
        {object}, getDocument(), new_position));
  }

  getDocument()->getUndoStack()->push(group_move_command);

  m_moving_items.clear();
}

void SelectionTool::endItemSelection() {
  if (getScene()) getScene()->removeItem(m_selection_rect.get());
}

void SelectionTool::refreshCursor() {
  Qt::CursorShape cursor_shape = Qt::ArrowCursor;

  switch (m_action) {
    case Action::NoAction: {
      const auto any_item_selected =
          getScene() != nullptr && !getScene()->selectedItems().empty();
      const auto any_item_hovered =
          getScene() != nullptr && !getScene()->hoveredItems().empty();

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

}  // namespace flow_document