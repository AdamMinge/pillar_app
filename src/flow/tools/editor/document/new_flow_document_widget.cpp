/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/new_flow_document_widget.h"
#include "flow/tools/editor/document/flow_document.h"
#include "flow/tools/editor/preferences_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewFlowDocumentWidget::Preferences
{

};

/* --------------------------- NewFlowDocumentWidget ------------------------ */

NewFlowDocumentWidget::NewFlowDocumentWidget(QWidget* parent) :
  NewDocumentWidget(parent),
  m_ui(new Ui::NewFlowDocumentWidget())
{
  m_ui->setupUi(this);

  m_ui->m_browser_edit->setBrowserCaption(tr("New Flow Document"));
  m_ui->m_browser_edit->setBrowserFilter(Document::getDocumentFileFilter(Document::Type::Flow));

  retranslateUi();
}

NewFlowDocumentWidget::~NewFlowDocumentWidget() = default;

std::unique_ptr<Document> NewFlowDocumentWidget::createDocument() const
{
  return nullptr;
}

bool NewFlowDocumentWidget::isValid() const
{
  return false;
}

void NewFlowDocumentWidget::changeEvent(QEvent* event)
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

void NewFlowDocumentWidget::retranslateUi()
{
  m_ui->retranslateUi(this);
}
