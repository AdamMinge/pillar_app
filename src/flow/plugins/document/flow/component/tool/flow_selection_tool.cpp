/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/tool/flow_selection_tool.h"
#include "flow/plugins/document/flow/component/tool/selection_rectangle.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ SelectionAction --------------------------- */

class SelectionAction : public FlowAbstractAction
{
public:
  explicit SelectionAction(QGraphicsScene *scene, const QPointF &start_pos);
  ~SelectionAction() override;

  void update(QGraphicsSceneMouseEvent *event) override;

private:
  QGraphicsScene *m_scene;
  QPointF m_start_pos;
  std::unique_ptr<SelectionRectangle> m_selection_rect;
};

SelectionAction::SelectionAction(
  QGraphicsScene *scene, const QPointF &start_pos)
    : m_scene(scene), m_start_pos(start_pos),
      m_selection_rect(std::make_unique<SelectionRectangle>())
{
  m_scene->addItem(m_selection_rect.get());
}

SelectionAction::~SelectionAction()
{
  m_scene->removeItem(m_selection_rect.get());
}

void SelectionAction::update(QGraphicsSceneMouseEvent *event)
{
  const auto mouse_pos = event->scenePos();
  m_selection_rect->setRect(QRectF(m_start_pos, mouse_pos).normalized());
}

/* ------------------------------ MovingItemAction -------------------------- */

class MovingItemAction : public FlowAbstractAction
{
public:
  explicit MovingItemAction();
  ~MovingItemAction() override;

  void update(QGraphicsSceneMouseEvent *event) override;
};

MovingItemAction::MovingItemAction() = default;

MovingItemAction::~MovingItemAction() = default;

void MovingItemAction::update(QGraphicsSceneMouseEvent *event) {}

/* ----------------------------- MovingSceneAction -------------------------- */

class MovingSceneAction : public FlowAbstractAction
{
public:
  explicit MovingSceneAction(QGraphicsView *view, const QPointF &start_pos);
  ~MovingSceneAction() override;

  void update(QGraphicsSceneMouseEvent *event) override;

private:
  QGraphicsView *m_view;
  QPointF m_start_pos;
};

MovingSceneAction::MovingSceneAction(
  QGraphicsView *view, const QPointF &start_pos)
    : m_view(view), m_start_pos(start_pos)
{}

MovingSceneAction::~MovingSceneAction() = default;

void MovingSceneAction::update(QGraphicsSceneMouseEvent *event)
{
  auto mouse_pos = event->scenePos();
  QPointF difference = m_start_pos - mouse_pos;

  m_view->setSceneRect(
    m_view->sceneRect().translated(difference.x(), difference.y()));
}

/* ----------------------------- FlowSelectionTool -------------------------- */

FlowSelectionTool::FlowSelectionTool(QObject *parent)
    : FlowAbstractTool(
        tr("Selection Tool"),
        QIcon(":/plugins/document/flow/images/32x32/selection_tool.png"),
        QCursor(), QKeySequence(Qt::Key_S), parent),
      m_action(nullptr), m_mouse_button(Qt::NoButton), m_mouse_click_pos(0, 0)
{}

FlowSelectionTool::~FlowSelectionTool() = default;

void FlowSelectionTool::activate(FlowScene *scene) {}

void FlowSelectionTool::deactivate(FlowScene *scene) {}

void FlowSelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mouseMoved(event);

  if (!m_action && m_mouse_button == Qt::LeftButton)
  {
    if (!(event->modifiers() & Qt::ShiftModifier))
    {
      m_action =
        std::make_unique<MovingSceneAction>(findView(event), m_mouse_click_pos);
    } else
    {
      m_action =
        std::make_unique<SelectionAction>(findScene(event), m_mouse_click_pos);
    }
  }

  if (m_action) m_action->update(event);
}

void FlowSelectionTool::mousePressed(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mousePressed(event);

  if (m_action) return;

  switch (event->button())
  {
    case Qt::LeftButton: {
      m_mouse_click_pos = event->scenePos();
      m_mouse_button = Qt::LeftButton;
      break;
    }

    default:
      break;
  }
}

void FlowSelectionTool::mouseReleased(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mouseReleased(event);

  m_action.reset(nullptr);
  m_mouse_button = Qt::NoButton;
}
