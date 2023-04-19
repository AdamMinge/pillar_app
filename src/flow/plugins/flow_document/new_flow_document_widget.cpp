/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/new_flow_document_widget.h"

#include "flow/plugins/flow_document/flow_document.h"
#include "flow/plugins/flow_document/flow_document_format.h"
/* ------------------------------------- Qt --------------------------------- */
#include <QMessageBox>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/format_helper.h>
#include <flow/libflow/preferences_manager.h>
#include <flow/libflow/project/project.h>
#include <flow/libflow/project/project_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

/* -------------------------------- Preferences ----------------------------- */

struct NewFlowDocumentWidget::Preferences {};

/* --------------------------- NewFlowDocumentWidget ------------------------ */

NewFlowDocumentWidget::NewFlowDocumentWidget(QWidget *parent)
    : flow::NewDocumentWidget(parent), m_ui(new Ui::NewFlowDocumentWidget()) {
  m_ui->setupUi(this);

  m_ui->m_name_and_path_filler->setPathValidations(
      utils::QtNameAndPathFiller::PathValidation::NotEmpty |
      utils::QtNameAndPathFiller::PathValidation::DirExists);

  const auto project = flow::ProjectManager::getInstance().getCurrentProject();
  const auto path = QFileInfo(project->getFileName()).absoluteDir().path();
  m_ui->m_name_and_path_filler->setPath(path);

  connect(m_ui->m_name_and_path_filler,
          &utils::QtNameAndPathFiller::validStateChanged, this,
          &NewFlowDocumentWidget::validate);

  retranslateUi();
}

NewFlowDocumentWidget::~NewFlowDocumentWidget() = default;

std::unique_ptr<flow::Document> NewFlowDocumentWidget::createDocument() {
  if (!isValid()) return nullptr;

  const auto name = m_ui->m_name_and_path_filler->getName();
  const auto path = m_ui->m_name_and_path_filler->getPath();

  return flow::NewDocumentWidget::createDocument<FlowDocument,
                                                 FlowDocumentFormat>(name,
                                                                     path);
}

void NewFlowDocumentWidget::changeEvent(QEvent *event) {
  QWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NewFlowDocumentWidget::retranslateUi() { m_ui->retranslateUi(this); }

void NewFlowDocumentWidget::validate() {
  auto valid = m_ui->m_name_and_path_filler->isValid();
  setValid(valid);
}

/* ------------------------ NewFlowDocumentWidgetFactory -------------------- */

NewFlowDocumentWidgetFactory::NewFlowDocumentWidgetFactory(QObject *parent)
    : flow::NewDocumentWidgetFactory(
          QIcon(":/plugins/document/flow/images/64x64/flow_document.png"),
          parent) {}

NewFlowDocumentWidgetFactory::~NewFlowDocumentWidgetFactory() = default;

std::unique_ptr<flow::NewDocumentWidget> NewFlowDocumentWidgetFactory::create()
    const {
  return std::make_unique<NewFlowDocumentWidget>();
}

}  // namespace plugin::flow_document
