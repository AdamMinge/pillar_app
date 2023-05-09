/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_dock.h"

#include "flow_document/component/factories/factories_tree_delegate.h"
#include "flow_document/component/factories/factories_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_factories_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesDock::FactoriesDock(QWidget *parent)
    : QDockWidget(parent),
      m_ui(new Ui::FactoriesDock()),
      m_factories_model(new FactoriesTreeModel),
      m_factories_filter_model(new QSortFilterProxyModel),
      m_factories_delegate(new FactoriesTreeDelegate) {
  setObjectName(QLatin1String("Factories"));

  initUi();
  initConnections();

  retranslateUi();
}

FactoriesDock::~FactoriesDock() = default;

void FactoriesDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void FactoriesDock::initUi() {
  m_ui->setupUi(this);

  m_factories_filter_model->setSourceModel(m_factories_model.get());

  m_ui->m_factories_view->setModel(m_factories_filter_model.get());
  m_ui->m_factories_view->setItemDelegate(m_factories_delegate.get());
}

void FactoriesDock::initConnections() {}

void FactoriesDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document