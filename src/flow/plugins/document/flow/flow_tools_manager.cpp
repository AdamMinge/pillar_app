/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_tools_manager.h"
#include "flow/plugins/document/flow/flow_abstract_tool.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<FlowToolsManager> FlowToolsManager::m_instance =
  QScopedPointer<FlowToolsManager>(nullptr);

FlowToolsManager &FlowToolsManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new FlowToolsManager);

  return *m_instance;
}

void FlowToolsManager::deleteInstance() { m_instance.reset(nullptr); }

void FlowToolsManager::setDocument(FlowDocument *document)
{
  if (m_document == document) return;

  m_document = document;

  auto actions = m_action_group->actions();
  for (auto action : actions)
  {
    auto tool = action->data().value<FlowAbstractTool *>();
    tool->setDocument(m_document);
  }
}

FlowDocument *FlowToolsManager::getDocument() const { return m_document; }

QAction *FlowToolsManager::registerTool(FlowAbstractTool *tool)
{
  tool->setDocument(m_document);

  auto action = new QAction(tool->getIcon(), tool->getName(), this);
  action->setShortcut(tool->getShortcut());
  action->setData(QVariant::fromValue<FlowAbstractTool *>(tool));
  action->setCheckable(true);
  action->setText(tool->getName());
  action->setEnabled(tool->isEnabled());
  action->setVisible(tool->isVisible());

  m_action_group->addAction(action);

  connect(
    tool, &FlowAbstractTool::enabledChanged, this,
    &FlowToolsManager::toolEnabledChanged);
  connect(
    tool, &FlowAbstractTool::visibleChanged, this,
    &FlowToolsManager::toolVisibleChanged);

  return action;
}

void FlowToolsManager::unregisterTool(FlowAbstractTool *tool)
{
  auto action = findAction(tool);
  Q_ASSERT(action);

  action->deleteLater();
  tool->disconnect(this);

  if (m_selected_tool == tool) m_selected_tool = nullptr;
}

bool FlowToolsManager::selectTool(FlowAbstractTool *tool)
{
  if (m_selected_tool == tool) return true;
  if (tool && !tool->isEnabled()) return false;

  if (auto action = findAction(tool))
  {
    action->trigger();
    return true;
  }

  return false;
}

FlowAbstractTool *FlowToolsManager::getSelectedTool() const
{
  return m_selected_tool;
}

QAction *FlowToolsManager::findAction(FlowAbstractTool *tool)
{
  auto actions = m_action_group->actions();
  for (auto action : actions)
  {
    auto action_tool = action->data().value<FlowAbstractTool *>();
    if (tool == action_tool) return action;
  }

  return nullptr;
}

FlowToolsManager::FlowToolsManager()
    : m_document(nullptr), m_action_group(new QActionGroup(this)),
      m_selected_tool(nullptr)
{
  m_action_group->setExclusive(true);

  connect(
    m_action_group, &QActionGroup::triggered, this,
    &FlowToolsManager::toolActivate);
}

FlowToolsManager::~FlowToolsManager() = default;

void FlowToolsManager::toolActivate(QAction *action)
{
  auto tool = action->data().value<FlowAbstractTool *>();
  Q_ASSERT(tool);

  if (m_selected_tool == tool) return;

  m_selected_tool = tool;

  Q_EMIT toolSelected(m_selected_tool);
}

void FlowToolsManager::toolEnabledChanged(bool enabled)
{
  auto action = qobject_cast<QAction *>(sender());
  Q_ASSERT(action);

  action->setEnabled(enabled);
}

void FlowToolsManager::toolVisibleChanged(bool visible)
{
  auto action = qobject_cast<QAction *>(sender());
  Q_ASSERT(action);

  action->setVisible(visible);
}