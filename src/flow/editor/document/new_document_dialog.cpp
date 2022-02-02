/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/document_type_list_delegate.h"
#include "flow/editor/document/document_type_list_model.h"
#include "flow/editor/document/flow/new_flow_document_widget.h"
#include "flow/editor/document/new_document_dialog.h"
#include "flow/editor/preferences_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "document/ui_new_document_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewDocumentDialog::Preferences {
  Preference<QByteArray> new_document_dialog_geometry =
    Preference<QByteArray>("new_document_dialog/geometry");
};

/* ----------------------------- NewDocumentDialog -------------------------- */

NewDocumentDialog::NewDocumentDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::NewDocumentDialog()),
      m_preferences(new Preferences),
      m_document_types_model(new DocumentTypeListModel()),
      m_document_types_delegate(new DocumentTypeListDelegate())
{
  initUi();
  initConnections();

  readSettings();
  retranslateUi();
}

NewDocumentDialog::~NewDocumentDialog() { writeSettings(); }

std::unique_ptr<api::IDocument> NewDocumentDialog::create()
{
  if (exec() != QDialog::Accepted) return nullptr;

  auto new_document_widget =
    dynamic_cast<NewDocumentWidget *>(m_ui->m_stacked_widget->currentWidget());
  Q_ASSERT(new_document_widget);

  return new_document_widget->createDocument();
}

void NewDocumentDialog::changeEvent(QEvent *event)
{
  QDialog::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NewDocumentDialog::documentTypeChanged(const QModelIndex &index)
{
  auto document_type = index.data(DocumentTypeListModel::Role::DocumentTypeRole)
                         .value<api::IDocument::Type>();

  auto prev_widget =
    dynamic_cast<NewDocumentWidget *>(m_ui->m_stacked_widget->currentWidget());
  auto next_widget = m_document_create_widgets[document_type];

  m_ui->m_stacked_widget->setCurrentWidget(next_widget);
  m_ui->m_create_button->setEnabled(next_widget->isValid());

  disconnect(prev_widget, &NewDocumentWidget::isValidChanged,
             m_ui->m_create_button, &QPushButton::setEnabled);
  connect(next_widget, &NewDocumentWidget::isValidChanged,
          m_ui->m_create_button, &QPushButton::setEnabled);
}

void NewDocumentDialog::updateCreateButton()
{
  m_ui->m_create_button->setEnabled(m_ui->m_name_and_path_filler->isValid());
}

void NewDocumentDialog::initUi()
{
  m_ui->setupUi(this);

  m_ui->m_name_and_path_filler->setPathValidations(
    utils::QtNameAndPathFiller::PathValidation::NotEmpty |
    utils::QtNameAndPathFiller::PathValidation::DirExists);

  m_ui->m_document_type_list->setModel(m_document_types_model.get());
  m_ui->m_document_type_list->setItemDelegate(m_document_types_delegate.get());

  m_document_types_delegate->setIconSize(QSize(64, 64));
  m_document_types_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_document_types_delegate->setSpacing(10, 15);

  m_document_create_widgets[api::IDocument::Type::Flow] =
    new NewFlowDocumentWidget(this);

  m_ui->m_stacked_widget->addWidget(
    m_document_create_widgets[api::IDocument::Type::Flow]);
  m_ui->m_stacked_widget->setCurrentWidget(
    m_document_create_widgets[api::IDocument::Type::Flow]);

  m_ui->m_document_type_list->setCurrentIndex(m_document_types_model->index(0));

  updateCreateButton();
}

void NewDocumentDialog::initConnections()
{
  connect(m_ui->m_create_button, &QPushButton::pressed, this,
          &NewDocumentDialog::accept);
  connect(m_ui->m_document_type_list->selectionModel(),
          &QItemSelectionModel::currentChanged, this,
          &NewDocumentDialog::documentTypeChanged);
  connect(m_ui->m_name_and_path_filler,
          &utils::QtNameAndPathFiller::validStateChanged, this,
          &NewDocumentDialog::updateCreateButton);
}

void NewDocumentDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("New Document"));
}

void NewDocumentDialog::writeSettings()
{
  m_preferences->new_document_dialog_geometry = saveGeometry();
}

void NewDocumentDialog::readSettings()
{
  auto new_document_dialog_geometry =
    m_preferences->new_document_dialog_geometry.get();
  if (!new_document_dialog_geometry.isNull())
    restoreGeometry(new_document_dialog_geometry);
}