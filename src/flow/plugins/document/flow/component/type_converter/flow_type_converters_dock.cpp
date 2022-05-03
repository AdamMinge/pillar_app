/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/type_converter/flow_type_converters_dock.h"
#include "flow/plugins/document/flow/component/type_converter/flow_type_converters_tree_delegate.h"
#include "flow/plugins/document/flow/component/type_converter/flow_type_converters_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ------------------------------------ Ui ---------------------------------- */
#include "document/flow/ui_flow_converters_dock.h"
/* -------------------------------------------------------------------------- */

FlowConvertersDock::FlowConvertersDock(QWidget *parent)
    : QDockWidget(parent), m_ui(new Ui::FlowConvertersDock()),
      m_type_converters_model(new FlowTypeConvertersTreeModel),
      m_converters_filter_model(new QSortFilterProxyModel),
      m_type_converters_delegate(new FlowTypeConvertersTreeDelegate)
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

  m_converters_filter_model->setSourceModel(m_type_converters_model.get());

  m_ui->m_converters_view->setModel(m_converters_filter_model.get());
  m_ui->m_converters_view->setItemDelegate(m_type_converters_delegate.get());
}

void FlowConvertersDock::initConnections() {}

void FlowConvertersDock::retranslateUi() { m_ui->retranslateUi(this); }