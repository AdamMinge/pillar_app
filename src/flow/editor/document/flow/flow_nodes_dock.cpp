/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_nodes_dock.h"
/* -------------------------------------------------------------------------- */

FlowNodesDock::FlowNodesDock(QWidget *parent) : QDockWidget(parent)
{
  setObjectName(QLatin1String("Nodes"));

  initUi();
  initConnections();

  retranslateUi();
}

FlowNodesDock::~FlowNodesDock() = default;

void FlowNodesDock::changeEvent(QEvent *event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void FlowNodesDock::initUi() {}

void FlowNodesDock::initConnections() {}

void FlowNodesDock::retranslateUi() { setWindowTitle(tr("Nodes")); }