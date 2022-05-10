/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/tool/flow_selection_tool.h"
#include "flow/plugins/document/flow/command/move_object.h"
#include "flow/plugins/document/flow/component/scene/flow_item.h"
#include "flow/plugins/document/flow/component/scene/flow_scene.h"
#include "flow/plugins/document/flow/component/tool/selection_rectangle.h"
#include "flow/plugins/document/flow/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
/* -------------------------------------------------------------------------- */

FlowSelectionTool::FlowSelectionTool(QObject *parent)
    : FlowAbstractTool(
        tr("Selection Tool"),
        QIcon(":/plugins/document/flow/images/32x32/selection_tool.png"),
        QKeySequence(Qt::Key_S), parent),
      m_action(Action::NoAction), m_mouse_clicked_button(Qt::MouseButton{}),
      m_selection_rect(std::make_unique<SelectionRectangle>()),
      m_clicked_item(nullptr), m_scene(nullptr)
{}

FlowSelectionTool::~FlowSelectionTool() = default;

void FlowSelectionTool::activate(FlowScene *scene) { m_scene = scene; }

void FlowSelectionTool::deactivate(FlowScene *scene) { m_scene = nullptr; }

void FlowSelectionTool::keyPressEvent(QKeyEvent *event)
{
  m_modifiers = event->modifiers();
  refreshCursor();
}

void FlowSelectionTool::keyReleaseEvent(QKeyEvent *event)
{
  m_modifiers = event->modifiers();
  refreshCursor();
}

void FlowSelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mouseMoved(event);

  const auto mouse_pos = event->scenePos();
  updateHover(mouse_pos);

  if (m_action == Action::NoAction && m_mouse_clicked_button == Qt::LeftButton)
  {
    auto drag_distance = (m_mouse_clicked_pos - mouse_pos).manhattanLength();
    if (drag_distance >= QApplication::startDragDistance() / 2.0)
    {
      const auto any_item_selected =
        m_scene != nullptr && !m_scene->selectedItems().empty();

      if (
        m_clicked_item ||
        ((m_modifiers & Qt::AltModifier) && any_item_selected) &&
          !(m_modifiers & Qt::ShiftModifier))
      {
        startItemMoving();
      } else if (m_modifiers & Qt::ShiftModifier)
      {
        startItemSelection();
      } else
      {
        startSceneMoving();
      }
    }
  }

  switch (m_action)
  {
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

void FlowSelectionTool::mousePressed(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mousePressed(event);

  if (m_action != Action::NoAction) return;

  switch (event->button())
  {
    case Qt::LeftButton: {
      m_mouse_clicked_button = Qt::LeftButton;
      m_mouse_clicked_pos = event->scenePos();

      if (m_scene)
      {
        auto item = m_scene->itemAt(m_mouse_clicked_pos, QTransform{});
        if (auto flow_item = dynamic_cast<FlowItem *>(item); flow_item)
          m_clicked_item = flow_item;
      }

      break;
    }

    default:
      break;
  }
}

void FlowSelectionTool::mouseReleased(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mouseReleased(event);

  switch (m_action)
  {
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
      if (m_clicked_item)
      {
        if (m_modifiers & Qt::ControlModifier)
        {
          m_clicked_item->setSelected(!m_clicked_item->isSelected());
        } else
        {
          m_scene->clearSelection();
          m_clicked_item->setSelected(true);
        }
      } else if (!(m_modifiers & (Qt::AltModifier | Qt::ControlModifier)))
      {
        m_scene->clearSelection();
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

void FlowSelectionTool::updateHover(const QPointF &mouse_pos)
{
  if (m_scene)
  {
    auto path = QPainterPath{};
    path.addEllipse(mouse_pos, 1, 1);
    m_scene->setHoveredArea(path);
  }
}

void FlowSelectionTool::startSceneMoving() { m_action = Action::SceneMoving; }

void FlowSelectionTool::startItemMoving()
{
  m_action = Action::ItemMoving;
  if (m_scene)
  {
    if (m_clicked_item && !(m_modifiers & Qt::AltModifier))
    {
      m_scene->clearSelection();
      m_clicked_item->setSelected(true);
    }

    for (auto item : m_scene->selectedItems())
    {
      if (auto flow_item = dynamic_cast<FlowItem *>(item); flow_item)
        m_moving_items.append(std::make_pair(flow_item, flow_item->pos()));
    }
  }
}

void FlowSelectionTool::startItemSelection()
{
  m_action = Action::ItemSelection;
  if (m_scene) m_scene->addItem(m_selection_rect.get());
}

void FlowSelectionTool::updateSceneMoving(const QPointF &mouse_pos)
{
  if (m_scene)
  {
    QPointF difference = m_mouse_clicked_pos - mouse_pos;

    m_scene->setSceneRect(
      m_scene->sceneRect().translated(difference.x(), difference.y()));
  }
}

void FlowSelectionTool::updateItemMoving(const QPointF &mouse_pos)
{
  QPointF difference = mouse_pos - m_mouse_clicked_pos;

  for (auto [selected_item, old_pos] : m_moving_items)
    selected_item->setPos(old_pos + difference);
}

void FlowSelectionTool::updateItemSelection(const QPointF &mouse_pos)
{
  if (m_scene)
  {
    m_selection_rect->setRect(
      QRectF(m_mouse_clicked_pos, mouse_pos).normalized());

    auto prev_selected_items = QList<QGraphicsItem *>{};
    if (m_modifiers & Qt::ControlModifier)
      prev_selected_items = m_scene->selectedItems();

    QPainterPath path;
    path.addRect(m_selection_rect->boundingRect());
    m_scene->setSelectionArea(path);

    for (auto prev_selected_item : prev_selected_items)
      prev_selected_item->setSelected(true);
  }
}

void FlowSelectionTool::endSceneMoving() {}

void FlowSelectionTool::endItemMoving()
{
  auto &[first_item, first_item_old_pos] = m_moving_items.front();
  auto objects = QList<flow::Object *>{};
  auto move = first_item->pos() - first_item_old_pos;

  for (auto &[moving_item, _] : m_moving_items)
    objects.append(moving_item->getObject());

  getDocument()->getUndoStack()->push(
    new MoveObject(getDocument(), objects, move));

  m_moving_items.clear();
}

void FlowSelectionTool::endItemSelection()
{
  if (m_scene) m_scene->removeItem(m_selection_rect.get());
}

void FlowSelectionTool::refreshCursor()
{
  Qt::CursorShape cursor_shape = Qt::ArrowCursor;

  switch (m_action)
  {
    case Action::NoAction: {
      const auto any_item_selected =
        m_scene != nullptr && !m_scene->selectedItems().empty();
      const auto any_item_hovered =
        m_scene != nullptr && !m_scene->hoveredItems().empty();

      if (
        any_item_hovered ||
        ((m_modifiers & Qt::AltModifier) && any_item_selected &&
         !(m_modifiers & Qt::ShiftModifier)))
      {
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
