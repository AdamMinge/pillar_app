/* ------------------------------------ Qt ---------------------------------- */
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/format_helper.h"
#include "flow/editor/preferences_manager.h"
#include "flow/editor/project/new_project_dialog.h"
#include "flow/editor/project/no_project_window.h"
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_manager.h"
#include "flow/editor/project/recent_project_list_delegate.h"
#include "flow/editor/project/recent_project_list_model.h"
/* ------------------------------------ Api --------------------------------- */
#include "flow/api/project_format.h"
/* ----------------------------------- Shared ------------------------------- */
#include <flow/utils/qtdialog/qtextendedfiledialog.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_no_project_window.h"
/* -------------------------------------------------------------------------- */

NoProjectWindow::NoProjectWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::NoProjectWindow),
      m_recent_projects_model(new RecentProjectListModel),
      m_recent_projects_delegate(new RecentProjectListDelegate),
      m_search_proxy_model(new QSortFilterProxyModel)
{
  initUi();
  initConnections();

  retranslateUi();
}

NoProjectWindow::~NoProjectWindow() = default;

void NoProjectWindow::changeEvent(QEvent *event)
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

PreferencesManager &NoProjectWindow::getPreferencesManager()
{
  return PreferencesManager::getInstance();
}

ProjectManager &NoProjectWindow::getProjectManager()
{
  return ProjectManager::getInstance();
}

void NoProjectWindow::openProject()
{
  const auto recent_project_files = getPreferencesManager().getRecentProjectFiles();
  const auto project_dir = recent_project_files.empty() ? QString{} : recent_project_files.last();
  const auto filter = FormatHelper<api::IProjectFormat>{api::IFileFormat::Capability::Read}.getFilter();

  const auto file_name = utils::QtExtendedFileDialog::getOpenFileName(
    this, tr("Open Project"), project_dir, filter);

  if (file_name.isEmpty())
    return;

  auto project = Project::load(file_name);
  auto project_ptr = project.get();

  if (project)
  {
    getProjectManager().addProject(std::move(project));
    getProjectManager().switchToProject(project_ptr);
  } else
  {
    QMessageBox::critical(this,
                          tr("Error Opening File"),
                          tr("Error opening '%1'").arg(file_name));
  }
}

void NoProjectWindow::createProject()
{
  auto new_project_dialog = QScopedPointer<NewProjectDialog>(new NewProjectDialog(this));
  if (auto project = new_project_dialog->create(); project)
  {
    auto project_ptr = project.get();

    getProjectManager().addProject(std::move(project));
    getProjectManager().switchToProject(project_ptr);
  }
}

void NoProjectWindow::openRecentProject(const QModelIndex &index)
{
  auto project_path = index.data(RecentProjectListModel::Role::ProjectPathRole).toString();
  getProjectManager().loadProject(project_path);

  //TODO Implementation
}

void NoProjectWindow::searchRecentProject(const QString &search)
{
  m_search_proxy_model->setFilterWildcard(search);
}

void NoProjectWindow::initUi()
{
  m_ui->setupUi(this);

  m_search_proxy_model->setSourceModel(m_recent_projects_model.get());
  m_ui->m_projects_list_view->setModel(m_search_proxy_model.get());
  m_ui->m_projects_list_view->setItemDelegate(m_recent_projects_delegate.get());

  m_recent_projects_delegate->setIconSize(QSize(64, 64));
  m_recent_projects_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_recent_projects_delegate->setSpacing(10, 15);

  m_search_proxy_model->setFilterRole(RecentProjectListModel::Role::ProjectNameRole);
}

void NoProjectWindow::initConnections()
{
  connect(m_ui->m_open_button, &QPushButton::pressed, this, &NoProjectWindow::openProject);
  connect(m_ui->m_new_project_button, &QPushButton::pressed, this, &NoProjectWindow::createProject);

  connect(m_ui->m_projects_list_view, &QListView::activated, this, &NoProjectWindow::openRecentProject);
  connect(m_ui->m_search_project_edit, &QLineEdit::textChanged, this, &NoProjectWindow::searchRecentProject);
}

void NoProjectWindow::retranslateUi()
{
  m_ui->retranslateUi(this);
}