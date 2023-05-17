/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/objects/objects_dock.h"

#include "flow_document/component/objects/objects_tree_model.h"
#include "flow_document/flow_document_action_handler.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QToolBar>
#include <QToolButton>
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

void ObjectsDock::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  m_document = document;

  m_objects_model->setDocument(m_document);
}

FlowDocument *ObjectsDock::getDocument() const { return m_document; }

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

  m_search_proxy_model->setSourceModel(m_objects_model.get());
  m_ui->m_objects_view->setModel(m_search_proxy_model.get());

  m_search_proxy_model->setFilterKeyColumn(
      ObjectsTreeModel::Column::NameColumn);
  m_search_proxy_model->setRecursiveFilteringEnabled(true);

  const auto &handler = FlowDocumentActionHandler::getInstance();

  auto buttons_container = new QToolBar();
  buttons_container->setFloatable(false);
  buttons_container->setMovable(false);
  buttons_container->setIconSize(QSize(16, 16));

  buttons_container->addAction(handler.getRemoveObjectAction());
  buttons_container->addAction(handler.getRaiseObjectAction());
  buttons_container->addAction(handler.getLowerObjectAction());
  buttons_container->addAction(handler.getDuplicateObjectAction());

  m_ui->m_toolbar_layout->addWidget(buttons_container);
}

void ObjectsDock::initConnections() {
  connect(m_ui->m_search_objects_edit, &QLineEdit::textChanged, this,
          &ObjectsDock::searchObjects);
}

void ObjectsDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document