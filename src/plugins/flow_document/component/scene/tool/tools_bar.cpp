/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/tools_bar.h"

#include "flow_document/component/scene/tool/selection_tool.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ToolsBar::ToolsBar(QWidget *parent)
    : QToolBar(parent),
      m_document(nullptr),
      m_action_group(new QActionGroup(this)),
      m_selected_tool(nullptr) {
  setObjectName(QLatin1String("ToolsBar"));

  initUi();
  initConnections();

  selectFirstTool();
}

ToolsBar::~ToolsBar() = default;

void ToolsBar::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  m_document = document;

  auto actions = m_action_group->actions();
  for (auto action : actions) {
    auto tool = action->data().value<AbstractTool *>();
    tool->setDocument(m_document);
  }
}

FlowDocument *ToolsBar::getDocument() const { return m_document; }

QAction *ToolsBar::registerTool(AbstractTool *tool) {
  tool->setDocument(m_document);

  auto action = new QAction(tool->getIcon(), tool->getName(), this);
  action->setShortcut(tool->getShortcut());
  action->setData(QVariant::fromValue<AbstractTool *>(tool));
  action->setCheckable(true);
  action->setText(tool->getName());
  action->setEnabled(tool->isEnabled());
  action->setVisible(tool->isVisible());

  m_action_group->addAction(action);

  connect(tool, &AbstractTool::enabledChanged, this,
          &ToolsBar::toolEnabledChanged);
  connect(tool, &AbstractTool::visibleChanged, this,
          &ToolsBar::toolVisibleChanged);

  return action;
}

void ToolsBar::unregisterTool(AbstractTool *tool) {
  auto action = findAction(tool);
  Q_ASSERT(action);

  action->deleteLater();
  tool->disconnect(this);

  if (m_selected_tool == tool) m_selected_tool = nullptr;
}

bool ToolsBar::selectTool(AbstractTool *tool) {
  if (m_selected_tool == tool) return true;
  if (tool && !tool->isEnabled()) return false;

  if (auto action = findAction(tool)) {
    action->trigger();
    return true;
  }

  return false;
}

AbstractTool *ToolsBar::getSelectedTool() const { return m_selected_tool; }

QAction *ToolsBar::findAction(AbstractTool *tool) {
  auto actions = m_action_group->actions();
  for (auto action : actions) {
    auto action_tool = action->data().value<AbstractTool *>();
    if (tool == action_tool) return action;
  }

  return nullptr;
}

void ToolsBar::toolActivate(QAction *action) {
  auto tool = action->data().value<AbstractTool *>();
  Q_ASSERT(tool);

  if (m_selected_tool == tool) return;

  m_selected_tool = tool;

  Q_EMIT toolSelected(m_selected_tool);
}

void ToolsBar::toolEnabledChanged(bool enabled) {
  auto action = qobject_cast<QAction *>(sender());
  Q_ASSERT(action);

  action->setEnabled(enabled);
}

void ToolsBar::toolVisibleChanged(bool visible) {
  auto action = qobject_cast<QAction *>(sender());
  Q_ASSERT(action);

  action->setVisible(visible);
}

void ToolsBar::initUi() {
  m_action_group->setExclusive(true);

  auto select_tool = new SelectionTool(this);
  addAction(registerTool(select_tool));
}

void ToolsBar::initConnections() {
  connect(m_action_group, &QActionGroup::triggered, this,
          &ToolsBar::toolActivate);
}

void ToolsBar::selectFirstTool() {
  auto action = m_action_group->actions().first();
  auto tool = action->data().value<AbstractTool *>();
  selectTool(tool);
}

}  // namespace flow_document