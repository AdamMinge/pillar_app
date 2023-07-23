/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/connections/connections_dock.h"

#include "flow_document/component/connections/connections_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_connections_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ConnectionsDock::ConnectionsDock(QWidget *parent)
    : FlowDockWidget(parent),
      m_ui(new Ui::ConnectionsDock()),
      m_connections_model(new ConnectionsTreeModel),
      m_filter_model(new OnlyConnectionsFilterProxyModel) {
  setObjectName(QLatin1String("Connections"));

  initUi();
  initConnections();

  retranslateUi();
}

ConnectionsDock::~ConnectionsDock() = default;

void ConnectionsDock::onDocumentChanged(FlowDocument *from, FlowDocument *to) {
  if (to) {
    m_ui->m_connections_view->header()->setSectionResizeMode(
        ConnectionsTreeModel::Column::NameColumn, QHeaderView::Stretch);
  }

  m_connections_model->setDocument(to);
  m_ui->m_connections_view->setDocument(to);
}

void ConnectionsDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ConnectionsDock::searchConnections(const QString &search) {
  m_filter_model->setFilterWildcard(search);
}

void ConnectionsDock::initUi() {
  m_ui->setupUi(this);

  m_filter_model->setSourceModel(m_connections_model.get());
  m_ui->m_connections_view->setModel(m_filter_model.get());

  m_filter_model->setFilterKeyColumn(ConnectionsTreeModel::Column::NameColumn);
  m_filter_model->setRecursiveFilteringEnabled(true);
}

void ConnectionsDock::initConnections() {
  connect(m_ui->m_search_connections_edit, &QLineEdit::textChanged, this,
          &ConnectionsDock::searchConnections);
}

void ConnectionsDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document