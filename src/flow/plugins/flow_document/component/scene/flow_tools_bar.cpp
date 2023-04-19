/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/component/scene/flow_tools_bar.h"

#include "flow/plugins/flow_document/component/scene/flow_selection_tool.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

FlowToolsBar::FlowToolsBar(QWidget *parent)
    : QToolBar(parent),
      m_document(nullptr),
      m_action_group(new QActionGroup(this)),
      m_selected_tool(nullptr) {
  setObjectName(QLatin1String("FlowToolsBar"));

  initUi();
  initConnections();

  selectFirstTool();
}

FlowToolsBar::~FlowToolsBar() = default;

void FlowToolsBar::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  m_document = document;

  auto actions = m_action_group->actions();
  for (auto action : actions) {
    auto tool = action->data().value<FlowAbstractTool *>();
    tool->setDocument(m_document);
  }
}

FlowDocument *FlowToolsBar::getDocument() const { return m_document; }

QAction *FlowToolsBar::registerTool(FlowAbstractTool *tool) {
  tool->setDocument(m_document);

  auto action = new QAction(tool->getIcon(), tool->getName(), this);
  action->setShortcut(tool->getShortcut());
  action->setData(QVariant::fromValue<FlowAbstractTool *>(tool));
  action->setCheckable(true);
  action->setText(tool->getName());
  action->setEnabled(tool->isEnabled());
  action->setVisible(tool->isVisible());

  m_action_group->addAction(action);

  connect(tool, &FlowAbstractTool::enabledChanged, this,
          &FlowToolsBar::toolEnabledChanged);
  connect(tool, &FlowAbstractTool::visibleChanged, this,
          &FlowToolsBar::toolVisibleChanged);

  return action;
}

void FlowToolsBar::unregisterTool(FlowAbstractTool *tool) {
  auto action = findAction(tool);
  Q_ASSERT(action);

  action->deleteLater();
  tool->disconnect(this);

  if (m_selected_tool == tool) m_selected_tool = nullptr;
}

bool FlowToolsBar::selectTool(FlowAbstractTool *tool) {
  if (m_selected_tool == tool) return true;
  if (tool && !tool->isEnabled()) return false;

  if (auto action = findAction(tool)) {
    action->trigger();
    return true;
  }

  return false;
}

FlowAbstractTool *FlowToolsBar::getSelectedTool() const {
  return m_selected_tool;
}

QAction *FlowToolsBar::findAction(FlowAbstractTool *tool) {
  auto actions = m_action_group->actions();
  for (auto action : actions) {
    auto action_tool = action->data().value<FlowAbstractTool *>();
    if (tool == action_tool) return action;
  }

  return nullptr;
}

void FlowToolsBar::toolActivate(QAction *action) {
  auto tool = action->data().value<FlowAbstractTool *>();
  Q_ASSERT(tool);

  if (m_selected_tool == tool) return;

  m_selected_tool = tool;

  Q_EMIT toolSelected(m_selected_tool);
}

void FlowToolsBar::toolEnabledChanged(bool enabled) {
  auto action = qobject_cast<QAction *>(sender());
  Q_ASSERT(action);

  action->setEnabled(enabled);
}

void FlowToolsBar::toolVisibleChanged(bool visible) {
  auto action = qobject_cast<QAction *>(sender());
  Q_ASSERT(action);

  action->setVisible(visible);
}

void FlowToolsBar::initUi() {
  m_action_group->setExclusive(true);

  auto select_tool = new FlowSelectionTool(this);
  addAction(registerTool(select_tool));
}

void FlowToolsBar::initConnections() {
  connect(m_action_group, &QActionGroup::triggered, this,
          &FlowToolsBar::toolActivate);
}

void FlowToolsBar::selectFirstTool() {
  auto action = m_action_group->actions().first();
  auto tool = action->data().value<FlowAbstractTool *>();
  selectTool(tool);
}

}  // namespace plugin::flow_document