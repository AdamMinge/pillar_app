/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/new_flow_document_widget.h"
#include "flow/libflow/preferences_manager.h"
#include "flow/plugins/document/flow/flow_document.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewFlowDocumentWidget::Preferences {
};

/* --------------------------- NewFlowDocumentWidget ------------------------ */

NewFlowDocumentWidget::NewFlowDocumentWidget(QWidget *parent)
    : INewDocumentWidget(parent), m_ui(new Ui::NewFlowDocumentWidget())
{
  m_ui->setupUi(this);

  retranslateUi();
}

NewFlowDocumentWidget::~NewFlowDocumentWidget() = default;

std::unique_ptr<api::document::IDocument>
NewFlowDocumentWidget::createDocument() const
{
  if (!isValid()) return nullptr;

  auto flow_document = FlowDocument::create();
  return flow_document;
}

bool NewFlowDocumentWidget::isValid() const { return true; }

void NewFlowDocumentWidget::changeEvent(QEvent *event)
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

void NewFlowDocumentWidget::retranslateUi() { m_ui->retranslateUi(this); }
