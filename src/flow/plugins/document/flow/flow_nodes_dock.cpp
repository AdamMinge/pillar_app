/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_nodes_dock.h"
#include "flow/plugins/document/flow/flow_nodes_tree_model.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/flow/ui_flow_nodes_dock.h"
/* -------------------------------------------------------------------------- */

FlowNodesDock::FlowNodesDock(QWidget *parent)
    : QDockWidget(parent), m_ui(new Ui::FlowNodesDock()),
      m_nodes_model(new FlowNodesTreeModel),
      m_nodes_filter_model(new QSortFilterProxyModel)
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

void FlowNodesDock::initUi()
{
  m_ui->setupUi(this);

  m_nodes_filter_model->setSourceModel(m_nodes_model.get());
  m_ui->m_nodes_view->setModel(m_nodes_filter_model.get());
}

void FlowNodesDock::initConnections() {}

void FlowNodesDock::retranslateUi() { m_ui->retranslateUi(this); }