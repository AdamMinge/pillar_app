/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_type_converters_dock.h"
#include "flow/plugins/document/flow/flow_type_converters_tree_model.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/flow/ui_flow_converters_dock.h"
/* -------------------------------------------------------------------------- */

FlowConvertersDock::FlowConvertersDock(QWidget *parent)
    : QDockWidget(parent), m_ui(new Ui::FlowConvertersDock()),
      m_converters_model(new FlowConvertersTreeModel),
      m_converters_filter_model(new QSortFilterProxyModel)
{
  setObjectName(QLatin1String("Converters"));

  initUi();
  initConnections();

  retranslateUi();
}

FlowConvertersDock::~FlowConvertersDock() = default;

void FlowConvertersDock::changeEvent(QEvent *event)
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

void FlowConvertersDock::initUi()
{
  m_ui->setupUi(this);

  m_converters_filter_model->setSourceModel(m_converters_model.get());
  m_ui->m_converters_view->setModel(m_converters_filter_model.get());
}

void FlowConvertersDock::initConnections() {}

void FlowConvertersDock::retranslateUi() { m_ui->retranslateUi(this); }