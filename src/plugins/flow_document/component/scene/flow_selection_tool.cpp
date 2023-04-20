/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_selection_tool.h"

#include "flow_document/command/move_object.h"
#include "flow_document/component/scene/flow_item.h"
#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/selection_rectangle.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowSelectionTool::FlowSelectionTool(QObject *parent)
    : FlowAbstractTool(
          tr("Selection Tool"),
          QIcon(":/plugins/flow_document/images/32x32/selection_tool.png"),
          QKeySequence(Qt::Key_S), parent),
      m_action(Action::NoAction),
      m_mouse_clicked_button(Qt::MouseButton{}),
      m_selection_rect(std::make_unique<SelectionRectangle>()),
      m_clicked_item(nullptr) {}

FlowSelectionTool::~FlowSelectionTool() = default;

void FlowSelectionTool::activate(FlowScene *scene) {
  FlowAbstractTool::activate(scene);
}

void FlowSelectionTool::deactivate() { FlowAbstractTool::deactivate(); }

void FlowSelectionTool::keyPressEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void FlowSelectionTool::keyReleaseEvent(QKeyEvent *event) {
  m_modifiers = event->modifiers();
  refreshCursor();
}

void FlowSelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event) {
  FlowAbstractTool::mouseMoved(event);

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
      } else {
        startSceneMoving();
      }
    }
  }

  switch (m_action) {
    case Action::ItemMoving:
      updateItemMoving(mouse_pos);
      break;

    case Action::SceneMoving:
      updateSceneMoving(mouse_pos);
      break;

    case Action::ItemSelection:
      updateItemSelection(mouse_pos);
      break;

    default:
      break;
  }

  refreshCursor();
}

void FlowSelectionTool::mousePressed(QGraphicsSceneMouseEvent *event) {
  FlowAbstractTool::mousePressed(event);

  if (m_action != Action::NoAction) return;

  switch (event->button()) {
    case Qt::LeftButton: {
      m_mouse_clicked_button = Qt::LeftButton;
      m_mouse_clicked_pos = event->scenePos();

      if (getScene()) {
        auto item = getScene()->itemAt(m_mouse_clicked_pos, QTransform{});
        if (auto flow_item = dynamic_cast<FlowItem *>(item); flow_item)
          m_clicked_item = flow_item;
      }

      break;
    }

    default:
      break;
  }
}

void FlowSelectionTool::mouseReleased(QGraphicsSceneMouseEvent *event) {
  FlowAbstractTool::mouseReleased(event);

  switch (m_action) {
    case Action::ItemMoving:
      endItemMoving();
      break;

    case Action::SceneMoving:
      endSceneMoving();
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

void FlowSelectionTool::updateHover(const QPointF &mouse_pos) {
  if (getScene()) {
    auto path = QPainterPath{};
    path.addEllipse(mouse_pos, 1, 1);
    getScene()->setHoveredArea(path);
  }
}

void FlowSelectionTool::startSceneMoving() { m_action = Action::SceneMoving; }

void FlowSelectionTool::startItemMoving() {
  m_action = Action::ItemMoving;
  if (getScene()) {
    if (m_clicked_item && !(m_modifiers & Qt::AltModifier)) {
      getScene()->clearSelection();
      m_clicked_item->setSelected(true);
    }

    for (auto item : getScene()->selectedItems()) {
      if (auto flow_item = dynamic_cast<FlowItem *>(item); flow_item)
        m_moving_items.append(std::make_pair(flow_item, flow_item->pos()));
    }
  }
}

void FlowSelectionTool::startItemSelection() {
  m_action = Action::ItemSelection;
  if (getScene()) getScene()->addItem(m_selection_rect.get());
}

void FlowSelectionTool::updateSceneMoving(const QPointF &mouse_pos) {
  if (getScene()) {
    QPointF difference = m_mouse_clicked_pos - mouse_pos;

    getScene()->setSceneRect(
        getScene()->sceneRect().translated(difference.x(), difference.y()));
  }
}

void FlowSelectionTool::updateItemMoving(const QPointF &mouse_pos) {
  QPointF difference = mouse_pos - m_mouse_clicked_pos;

  for (auto [selected_item, old_pos] : m_moving_items)
    selected_item->setPos(old_pos + difference);
}

void FlowSelectionTool::updateItemSelection(const QPointF &mouse_pos) {
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

void FlowSelectionTool::endSceneMoving() {}

void FlowSelectionTool::endItemMoving() {
  auto &[first_item, first_item_old_pos] = m_moving_items.front();
  auto objects = QList<Object *>{};
  auto move = first_item->pos() - first_item_old_pos;

  for (auto &[moving_item, _] : m_moving_items)
    objects.append(moving_item->getObject());

  getDocument()->getUndoStack()->push(
      new MoveObject(getDocument(), objects, move));

  m_moving_items.clear();
}

void FlowSelectionTool::endItemSelection() {
  if (getScene()) getScene()->removeItem(m_selection_rect.get());
}

void FlowSelectionTool::refreshCursor() {
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
    case Action::SceneMoving:
      cursor_shape = Qt::SizeAllCursor;
      break;

    default:
      break;
  }

  setCursor(cursor_shape);
}

}  // namespace flow_document