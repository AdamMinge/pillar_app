/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_selection_tool.h"
/* -------------------------------------------------------------------------- */

FlowSelectionTool::FlowSelectionTool(QObject *parent)
    : FlowAbstractTool(
        tr("Selection Tool"),
        QIcon(":/plugins/document/flow/images/32x32/selection_tool.png"),
        QCursor(), QKeySequence(Qt::Key_S), parent),
      m_action(Action::NoAction), m_mouse_button(Qt::NoButton),
      m_mouse_click_pos(0, 0)
{}

FlowSelectionTool::~FlowSelectionTool() = default;

void FlowSelectionTool::activate(FlowScene *scene) {}

void FlowSelectionTool::deactivate(FlowScene *scene) {}

void FlowSelectionTool::mouseMoved(QGraphicsSceneMouseEvent *event)
{
  FlowAbstractTool::mouseMoved(event);

  if (m_action == Action::NoAction && m_mouse_button == Qt::LeftButton)
  {
    if (!(event->modifiers() & Qt::ShiftModifier))
    {
      startMovingAction();
    } else
    {
      startSelectingAction();
    }
  }

  switch (m_action)
  {
    case Action::Selecting:
      updateSelectingAction();
      break;

    case Action::Moving:
      updateMovingAction();
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

  switch (m_action)
  {
    case Action::Selecting:
      endSelectingAction();
      break;

    case Action::Moving:
      endMovingAction();
      break;

    default:
      break;
  }

  m_mouse_button = Qt::NoButton;
}

void FlowSelectionTool::startSelectingAction() { m_action = Action::Selecting; }

void FlowSelectionTool::updateSelectingAction() {}

void FlowSelectionTool::endSelectingAction() { m_action = Action::NoAction; }

void FlowSelectionTool::startMovingAction() { m_action = Action::Moving; }

void FlowSelectionTool::updateMovingAction() {}

void FlowSelectionTool::endMovingAction() { m_action = Action::NoAction; }