/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/new_flow_document_widget.h"
#include "flow/plugins/document/flow/flow_document.h"
#include "flow/plugins/document/flow/flow_document_format.h"
/* ------------------------------------- Qt --------------------------------- */
#include <QMessageBox>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/format_helper.h>
#include <flow/libflow/preferences_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewFlowDocumentWidget::Preferences {
};

/* --------------------------- NewFlowDocumentWidget ------------------------ */

NewFlowDocumentWidget::NewFlowDocumentWidget(QWidget *parent)
    : flow::document::NewDocumentWidget(parent),
      m_ui(new Ui::NewFlowDocumentWidget())
{
  m_ui->setupUi(this);

  m_ui->m_name_and_path_filler->setPathValidations(
    utils::QtNameAndPathFiller::PathValidation::NotEmpty |
    utils::QtNameAndPathFiller::PathValidation::DirExists);

  connect(
    m_ui->m_name_and_path_filler,
    &utils::QtNameAndPathFiller::validStateChanged, this,
    &NewFlowDocumentWidget::validate);

  retranslateUi();
}

NewFlowDocumentWidget::~NewFlowDocumentWidget() = default;

std::unique_ptr<flow::document::Document>
NewFlowDocumentWidget::createDocument()
{
  if (!isValid()) return nullptr;

  auto format_helper =
    flow::FormatHelper<FlowDocumentFormat>{flow::FileFormat::Capability::Write};
  auto format = format_helper.getFormats().isEmpty()
                  ? nullptr
                  : format_helper.getFormats().front();

  auto error = tr("Wrong document format");
  if (format)
  {
    auto document = FlowDocument::create();
    document->setWriterFormat(format);
    document->setWriterFormat(format);

    const auto name = m_ui->m_name_and_path_filler->getName();
    const auto path = m_ui->m_name_and_path_filler->getPath();
    const auto file_name =
      QDir(path).filePath(name + "." + format->getShortName());

    if (document->save(file_name, &error)) return document;
  }

  QMessageBox::critical(this, tr("Error Document Creation"), error);
  return nullptr;
}

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

void NewFlowDocumentWidget::validate()
{
  auto valid = m_ui->m_name_and_path_filler->isValid();
  setValid(valid);
}

/* ------------------------ NewFlowDocumentWidgetFactory -------------------- */

NewFlowDocumentWidgetFactory::NewFlowDocumentWidgetFactory(QObject *parent)
    : flow::document::NewDocumentWidgetFactory(
        QIcon(":/plugins/document/flow/images/64x64/flow_document.png"), parent)
{}

NewFlowDocumentWidgetFactory::~NewFlowDocumentWidgetFactory() = default;

std::unique_ptr<flow::document::NewDocumentWidget>
NewFlowDocumentWidgetFactory::create() const
{
  return std::make_unique<NewFlowDocumentWidget>();
}
