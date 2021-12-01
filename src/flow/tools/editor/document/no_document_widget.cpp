/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/no_document_widget.h"
#include "flow/tools/editor/document/document_manager.h"
#include "flow/tools/editor/document/document_list_delegate.h"
#include "flow/tools/editor/document/document_list_model.h"
#include "flow/tools/editor/action_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_no_document_widget.h"
/* -------------------------------------------------------------------------- */

NoDocumentWidget::NoDocumentWidget(QWidget* parent) :
  QWidget(parent),
  m_ui(new Ui::NoDocumentWidget()),
  m_documents_model(new DocumentListModel()),
  m_documents_delegate(new DocumentListDelegate()),
  m_search_proxy_model(new QSortFilterProxyModel())
{
  m_ui->setupUi(this);

  connect(m_ui->m_new_document_button, &QPushButton::pressed, ActionManager::getInstance().findAction("new_document"), &QAction::trigger);
  connect(m_ui->m_open_button, &QPushButton::pressed, ActionManager::getInstance().findAction("open_document"), &QAction::trigger);
  connect(m_ui->m_documents_list_view, &QListView::activated, this, &NoDocumentWidget::openDocument);
  connect(m_ui->m_search_document_edit, &QLineEdit::textChanged, this, &NoDocumentWidget::searchDocument);

  m_search_proxy_model->setSourceModel(m_documents_model.get());
  m_ui->m_documents_list_view->setModel(m_search_proxy_model.get());
  m_ui->m_documents_list_view->setItemDelegate(m_documents_delegate.get());

  m_documents_delegate->setIconSize(QSize(64, 64));
  m_documents_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_documents_delegate->setSpacing(10, 15);

  m_search_proxy_model->setFilterRole(DocumentListModel::Role::DocumentNameRole);

  retranslateUi();
}

NoDocumentWidget::~NoDocumentWidget() = default;

void NoDocumentWidget::changeEvent(QEvent* event)
{
  QWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NoDocumentWidget::openDocument(const QModelIndex& index) // NOLINT(readability-convert-member-functions-to-static)
{
  auto document_path = index.data(DocumentListModel::Role::DocumentPathRole).toString();
  DocumentManager::getInstance().loadDocument(document_path);
}

void NoDocumentWidget::searchDocument(const QString& search)
{
  m_search_proxy_model->setFilterWildcard(search);
}

void NoDocumentWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}