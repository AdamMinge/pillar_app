/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/objects/objects_dock.h"

#include "flow_document/component/objects/objects_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_objects_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectsDock::ObjectsDock(QWidget *parent)
    : QDockWidget(parent),
      m_ui(new Ui::ObjectsDock()),
      m_objects_model(new ObjectsTreeModel),
      m_search_proxy_model(new QSortFilterProxyModel) {
  setObjectName(QLatin1String("Objects"));

  initUi();
  initConnections();

  retranslateUi();
}

ObjectsDock::~ObjectsDock() = default;

void ObjectsDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ObjectsDock::searchObjects(const QString &search) {
  m_search_proxy_model->setFilterWildcard(search);
}

void ObjectsDock::initUi() {
  m_ui->setupUi(this);

  // TODO - Uncomment when finish tree model impl

  // m_search_proxy_model->setSourceModel(m_objects_model.get());
  // m_ui->m_objects_view->setModel(m_search_proxy_model.get());

  // m_search_proxy_model->setFilterRole(ObjectsTreeModel::Role::NameRole);
  // m_search_proxy_model->setRecursiveFilteringEnabled(true);
}

void ObjectsDock::initConnections() {
  connect(m_ui->m_search_objects_edit, &QLineEdit::textChanged, this,
          &ObjectsDock::searchObjects);
}

void ObjectsDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document