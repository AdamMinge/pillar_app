/* ----------------------------------- Local -------------------------------- */
#include "flow_document/new_flow_document_widget.h"

#include "flow_document/flow_document.h"
#include "flow_document/flow_document_format.h"
#include "flow_document/resources.h"
/* ------------------------------------- Qt --------------------------------- */
#include <QMessageBox>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/format_helper.h>
#include <pillar/preferences_manager.h>
#include <pillar/project/project.h>
#include <pillar/project/project_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- Preferences ----------------------------- */

struct NewFlowDocumentWidget::Preferences {};

/* --------------------------- NewFlowDocumentWidget ------------------------ */

NewFlowDocumentWidget::NewFlowDocumentWidget(QWidget *parent)
    : pillar::NewDocumentWidget(parent), m_ui(new Ui::NewFlowDocumentWidget()) {
  m_ui->setupUi(this);

  m_ui->m_name_and_path_filler->setPathValidations(
      qtils::QtNameAndPathFiller::PathValidation::NotEmpty |
      qtils::QtNameAndPathFiller::PathValidation::DirExists);

  const auto project =
      pillar::ProjectManager::getInstance().getCurrentProject();
  const auto path = QFileInfo(project->getFileName()).absoluteDir().path();
  m_ui->m_name_and_path_filler->setPath(path);

  connect(m_ui->m_name_and_path_filler,
          &qtils::QtNameAndPathFiller::validStateChanged, this,
          &NewFlowDocumentWidget::validate);

  retranslateUi();
}

NewFlowDocumentWidget::~NewFlowDocumentWidget() = default;

std::unique_ptr<pillar::Document> NewFlowDocumentWidget::createDocument() {
  if (!isValid()) return nullptr;

  const auto name = m_ui->m_name_and_path_filler->getName();
  const auto path = m_ui->m_name_and_path_filler->getPath();

  return pillar::NewDocumentWidget::createDocument<FlowDocument,
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
    : pillar::NewDocumentWidgetFactory(QIcon(icons::x64::FlowDocument),
                                       parent) {}

NewFlowDocumentWidgetFactory::~NewFlowDocumentWidgetFactory() = default;

pillar::NewDocumentWidget *NewFlowDocumentWidgetFactory::create(
    QWidget *parent) const {
  return new NewFlowDocumentWidget(parent);
}

}  // namespace flow_document
