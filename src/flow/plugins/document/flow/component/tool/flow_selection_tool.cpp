/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/tool/flow_selection_tool.h"
#include "flow/plugins/document/flow/component/scene/flow_item.h"
#include "flow/plugins/document/flow/component/scene/flow_scene.h"
#include "flow/plugins/document/flow/component/scene/flow_view.h"
#include "flow/plugins/document/flow/component/tool/selection_rectangle.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
/* -------------------------------------------------------------------------- */

FlowSelectionTool::FlowSelectionTool(QObject *parent)
    : FlowAbstractTool(
        tr("Selection Tool"),
        QIcon(":/plugins/document/flow/images/32x32/selection_tool.png"),
        QCursor(), QKeySequence(Qt::Key_S), parent),
      m_action(Action::NoAction), m_mouse_clicked_button(Qt::MouseButton{}),
      m_selection_rect(std::make_unique<SelectionRectangle>()),
      m_clicked_item(nullptr)
{}

FlowSelectionTool::~FlowSelectionTool() = default;

void FlowSelectionTool::activate(FlowScene *scene) {}

void FlowSelectionTool::deactivate(FlowScene *scene) {}

void FlowSelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mouseMoved(event);

  updateHover(event);

  if (m_action == Action::NoAction && m_mouse_clicked_button == Qt::LeftButton)
  {
    const auto modifiers = event->modifiers();
    const auto mouse_pos = event->scenePos();

    auto drag_distance = (m_mouse_clicked_pos - mouse_pos).manhattanLength();
    if (drag_distance >= QApplication::startDragDistance() / 2.0)
    {
      auto scene = findScene(event);
      const auto any_item_selected =
        scene != nullptr && !scene->selectedItems().empty();

      if (
        m_clicked_item ||
        ((modifiers & Qt::AltModifier) && any_item_selected) &&
          !(modifiers & Qt::ShiftModifier))
      {
        startItemMoving(event);
      } else if (modifiers & Qt::ShiftModifier)
      {
        startItemSelection(event);
      } else
      {
        startSceneMoving(event);
      }
    }
  }

  switch (m_action)
  {
    case Action::ItemMoving:
      updateItemMoving(event);
      break;

    case Action::SceneMoving:
      updateSceneMoving(event);
      break;

    case Action::ItemSelection:
      updateItemSelection(event);
      break;

    default:
      break;
  }
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

      if (auto scene = findScene(event); scene)
        m_clicked_item = scene->itemAt(m_mouse_clicked_pos, QTransform{});

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
      endItemMoving(event);
      break;

    case Action::SceneMoving:
      endSceneMoving(event);
      break;

    case Action::ItemSelection:
      endItemSelection(event);
      break;

    case Action::NoAction: {
      const auto modifiers = event->modifiers();
      if (m_clicked_item)
      {
        if (modifiers & Qt::ControlModifier)
        {
          m_clicked_item->setSelected(!m_clicked_item->isSelected());
        } else
        {
          findScene(event)->clearSelection();
          m_clicked_item->setSelected(true);
        }
      } else if (!(modifiers & (Qt::AltModifier | Qt::ControlModifier)))
      {
        findScene(event)->clearSelection();
      }
      break;
    }
  }

  m_action = Action::NoAction;
  m_mouse_clicked_pos = QPointF{};
  m_mouse_clicked_button = Qt::MouseButton{};
  m_clicked_item = nullptr;
}

void FlowSelectionTool::updateHover(QGraphicsSceneMouseEvent *event)
{
  if (auto scene = qobject_cast<FlowScene *>(findScene(event)); scene)
  {
    auto mouse_pos = event->scenePos();
    auto path = QPainterPath{};
    path.addEllipse(mouse_pos, 1, 1);
    scene->setHoveredArea(path);
  }
}

void FlowSelectionTool::startSceneMoving(QGraphicsSceneMouseEvent *event)
{
  m_action = Action::SceneMoving;
}

void FlowSelectionTool::startItemMoving(QGraphicsSceneMouseEvent *event)
{
  m_action = Action::ItemMoving;
  if (auto scene = qobject_cast<FlowScene *>(findScene(event)); scene)
  {
    if (m_clicked_item && !(event->modifiers() & Qt::AltModifier))
    {
      scene->clearSelection();
      m_clicked_item->setSelected(true);
    }

    for (auto item : scene->selectedItems())
      m_moving_items.append(std::make_pair(item, item->pos()));
  }
}

void FlowSelectionTool::startItemSelection(QGraphicsSceneMouseEvent *event)
{
  m_action = Action::ItemSelection;
  if (auto scene = qobject_cast<FlowScene *>(findScene(event)); scene)
    scene->addItem(m_selection_rect.get());
}

void FlowSelectionTool::updateSceneMoving(QGraphicsSceneMouseEvent *event)
{
  if (auto view = qobject_cast<FlowView *>(findView(event)); view)
  {
    auto mouse_pos = event->scenePos();
    QPointF difference = m_mouse_clicked_pos - mouse_pos;

    view->setSceneRect(
      view->sceneRect().translated(difference.x(), difference.y()));
  }
}

void FlowSelectionTool::updateItemMoving(QGraphicsSceneMouseEvent *event)
{
  auto mouse_pos = event->scenePos();
  QPointF difference = mouse_pos - m_mouse_clicked_pos;

  for (auto [selected_item, old_pos] : m_moving_items)
    selected_item->setPos(old_pos + difference);
}

void FlowSelectionTool::updateItemSelection(QGraphicsSceneMouseEvent *event)
{
  if (auto scene = qobject_cast<FlowScene *>(findScene(event)); scene)
  {
    const auto mouse_pos = event->scenePos();
    m_selection_rect->setRect(
      QRectF(m_mouse_clicked_pos, mouse_pos).normalized());

    auto prev_selected_items = QList<QGraphicsItem *>{};
    if (event->modifiers() & Qt::ControlModifier)
      prev_selected_items = scene->selectedItems();

    QPainterPath path;
    path.addRect(m_selection_rect->boundingRect());
    scene->setSelectionArea(path);

    for (auto prev_selected_item : prev_selected_items)
      prev_selected_item->setSelected(true);
  }
}

void FlowSelectionTool::endSceneMoving(QGraphicsSceneMouseEvent *event) {}

void FlowSelectionTool::endItemMoving(QGraphicsSceneMouseEvent *event)
{
  m_moving_items.clear();
}

void FlowSelectionTool::endItemSelection(QGraphicsSceneMouseEvent *event)
{
  if (auto scene = qobject_cast<FlowScene *>(findScene(event)); scene)
    scene->removeItem(m_selection_rect.get());
}
