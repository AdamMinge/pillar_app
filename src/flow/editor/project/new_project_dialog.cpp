/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QEvent>
#include <QFileInfo>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/format_helper.h"
#include "flow/editor/preferences_manager.h"
#include "flow/editor/project/new_project_dialog.h"
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_format_pro.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_project_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewProjectDialog::Preferences {
  Preference<QByteArray> new_project_dialog_geometry = Preference<QByteArray>("new_project_dialog/geometry");
};

/* ----------------------------- NewProjectDialog -------------------------- */

NewProjectDialog::NewProjectDialog(QWidget *parent)
    : QDialog(parent),
      m_ui(new Ui::NewProjectDialog()),
      m_preferences(new Preferences)
{
  m_ui->setupUi(this);

  initUi();
  initConnections();

  readSettings();
  retranslateUi();
}

NewProjectDialog::~NewProjectDialog()
{
  writeSettings();
}

std::unique_ptr<api::IProject> NewProjectDialog::create()
{
  if (exec() != QDialog::Accepted)
    return nullptr;


  auto format_helper = FormatHelper<ProjectFormatPro>{api::IFileFormat::Capability::Write};
  auto format = format_helper.getFormats().isEmpty() ? nullptr : format_helper.getFormats().front();

  QString error = tr("Wrong project format");
  if (format)
  {
    auto project = Project::create();
    project->setWriterFormat(format);
    project->setWriterFormat(format);

    const auto name = m_ui->m_project_name_edit->text();
    const auto path = m_ui->m_project_path_edit->text();
    const auto file_name = QDir(path).filePath(name + "." + format->getShortName());

    if (project->save(file_name, &error))
      return project;
  }

  QMessageBox::critical(this, tr("Error Project Creation"), error);
  return nullptr;
}

void NewProjectDialog::projectNameChanged()
{
  const auto name = m_ui->m_project_name_edit->text();

  auto error_message = QString{};
  if (name.isEmpty())
    error_message = tr("Please enter some name");

  m_ui->m_project_name_error_message->setVisible(!error_message.isEmpty());
  m_ui->m_project_name_error_message->setText(error_message);

  updateCreateButton();
}

void NewProjectDialog::projectPathChanged()
{
  const auto path = m_ui->m_project_path_edit->text();

  auto file_info = QFileInfo{path};
  auto dir = QDir{path};

  auto path_is_incorrect = !file_info.exists() || ((!file_info.isDir()) || (!file_info.isWritable()));
  auto dir_is_empty = !dir.isEmpty();

  auto error_message = QString{};
  if (path_is_incorrect || dir_is_empty)
    error_message = tr("Please choose an empty folder");

  m_ui->m_project_path_error_message->setVisible(!error_message.isEmpty());
  m_ui->m_project_path_error_message->setText(error_message);

  updateCreateButton();
}

void NewProjectDialog::updateCreateButton()
{
  const auto path_error = m_ui->m_project_path_error_message->text();
  m_ui->m_create_button->setEnabled(path_error.isEmpty());
}

void NewProjectDialog::changeEvent(QEvent *event)
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


void NewProjectDialog::initUi()
{
  m_ui->m_project_path_edit->setBrowserCaption(tr("Select Project Directory"));
  m_ui->m_project_path_edit->setBrowserDir(QString{});

  projectNameChanged();
  projectPathChanged();
}

void NewProjectDialog::initConnections()
{
  connect(m_ui->m_project_name_edit, &QLineEdit::textChanged, this, &NewProjectDialog::projectNameChanged);
  connect(m_ui->m_project_path_edit, &QLineEdit::textChanged, this, &NewProjectDialog::projectPathChanged);

  connect(m_ui->m_create_button, &QPushButton::pressed, this, &NewProjectDialog::accept);
}

void NewProjectDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("New Project"));
}

void NewProjectDialog::writeSettings()
{
  m_preferences->new_project_dialog_geometry = saveGeometry();
}

void NewProjectDialog::readSettings()
{
  auto new_project_dialog_geometry = m_preferences->new_project_dialog_geometry.get();
  if (!new_project_dialog_geometry.isNull()) restoreGeometry(new_project_dialog_geometry);
}
