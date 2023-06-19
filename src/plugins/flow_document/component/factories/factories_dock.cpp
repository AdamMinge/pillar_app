/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_dock.h"

#include "flow_document/component/factories/factories_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/model/leaf_filter_proxy_model.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_factories_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesDock::FactoriesDock(QWidget *parent)
    : FlowDockWidget(parent),
      m_ui(new Ui::FactoriesDock()),
      m_factories_model(new FactoriesTreeModel),
      m_search_proxy_model(new utils::QtLeafFilterProxyModel) {
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

void FactoriesDock::searchFactories(const QString &search) {
  m_search_proxy_model->setFilterWildcard(search);
}

void FactoriesDock::initUi() {
  m_ui->setupUi(this);

  m_search_proxy_model->setSourceModel(m_factories_model.get());
  m_ui->m_factories_view->setModel(m_search_proxy_model.get());

  m_search_proxy_model->setFilterKeyColumn(
      FactoriesTreeModel::Column::NameColumn);
  m_search_proxy_model->setRecursiveFilteringEnabled(true);
}

void FactoriesDock::initConnections() {
  connect(m_ui->m_search_factories_edit, &QLineEdit::textChanged, this,
          &FactoriesDock::searchFactories);
}

void FactoriesDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document