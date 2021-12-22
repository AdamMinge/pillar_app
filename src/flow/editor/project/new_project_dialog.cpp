/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/preferences_manager.h"
#include "flow/editor/project/new_project_dialog.h"
#include "flow/editor/project/project.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_project_dialog.h"
/* ------------------------------------ Ui ---------------------------------- */

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

  connect(m_ui->m_create_button, &QPushButton::pressed, this, &NewProjectDialog::accept);

  readSettings();
  retranslateUi();
}

NewProjectDialog::~NewProjectDialog()
{
  writeSettings();
}

std::unique_ptr<Project> NewProjectDialog::create()
{
  if (exec() != QDialog::Accepted)
    return nullptr;

  return Project::create();
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
