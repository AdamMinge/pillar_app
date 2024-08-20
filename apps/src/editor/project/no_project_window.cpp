/* ------------------------------------ Qt ---------------------------------- */
#include <QMessageBox>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/format_helper.h>
#include <pillar/preferences_manager.h>
#include <pillar/project/project.h>
#include <pillar/project/project_format.h>
#include <pillar/project/project_manager.h>
/* ----------------------------------- Local -------------------------------- */
#include "project/new_project_dialog.h"
#include "project/no_project_window.h"
#include "project/recent_project_list_delegate.h"
#include "project/recent_project_list_model.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/dialog/extended_file_dialog.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_no_project_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NoProjectWindow::Preferences {
  pillar::Preference<QByteArray> no_project_window_geometry =
      pillar::Preference<QByteArray>("no_project_window/geometry");
  pillar::Preference<QByteArray> no_project_window_state =
      pillar::Preference<QByteArray>("no_project_window/state");
};

/* ------------------------------ NoProjectWindow --------------------------- */

NoProjectWindow::NoProjectWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::NoProjectWindow),
      m_preferences(new Preferences),
      m_recent_projects_model(new RecentProjectListModel),
      m_recent_projects_delegate(new RecentProjectListDelegate),
      m_search_proxy_model(new QSortFilterProxyModel) {
  initUi();
  initConnections();

  retranslateUi();
}

NoProjectWindow::~NoProjectWindow() = default;

void NoProjectWindow::writeSettings() {
  m_preferences->no_project_window_geometry = saveGeometry();
  m_preferences->no_project_window_state = saveState();
}

void NoProjectWindow::readSettings() {
  auto window_geometry = m_preferences->no_project_window_geometry.get();
  auto window_state = m_preferences->no_project_window_state.get();

  if (!window_geometry.isNull()) restoreGeometry(window_geometry);
  if (!window_state.isNull()) restoreState(window_state);
}

void NoProjectWindow::changeEvent(QEvent *event) {
  QWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NoProjectWindow::openProject() {
  const auto recent_project_files =
      pillar::PreferencesManager::getInstance().getRecentProjectFiles();
  const auto project_dir =
      recent_project_files.empty() ? QString{} : recent_project_files.last();
  const auto filter =
      pillar::FormatHelper<pillar::ProjectFormat>{
          pillar::FileFormat::Capability::Read}
          .getFilter();

  const auto file_name = qtils::QtExtendedFileDialog::getOpenFileName(
      this, tr("Open Project"), project_dir, filter);

  if (file_name.isEmpty()) return;

  QString error;
  if (!pillar::ProjectManager::getInstance().loadProject(file_name, &error)) {
    QMessageBox::critical(this, tr("Error Opening File"), error);
    return;
  }

  pillar::PreferencesManager::getInstance().addRecentProjectFile(file_name);
}

void NoProjectWindow::createProject() {
  auto new_project_dialog =
      QScopedPointer<NewProjectDialog>(new NewProjectDialog(this));
  if (auto project = new_project_dialog->create(); project) {
    auto project_ptr = project.get();

    pillar::ProjectManager::getInstance().addProject(std::move(project));
    pillar::PreferencesManager::getInstance().addRecentProjectFile(
        project_ptr->getFileName());
  }
}

void NoProjectWindow::openRecentProject(const QModelIndex &index) {
  auto project_path =
      index.data(RecentProjectListModel::Role::ProjectPathRole).toString();
  pillar::ProjectManager::getInstance().loadProject(project_path);
}

void NoProjectWindow::searchRecentProject(const QString &search) {
  m_search_proxy_model->setFilterWildcard(search);
}

void NoProjectWindow::initUi() {
  m_ui->setupUi(this);

  m_search_proxy_model->setSourceModel(m_recent_projects_model.get());
  m_ui->m_projects_list_view->setModel(m_search_proxy_model.get());
  m_ui->m_projects_list_view->setItemDelegate(m_recent_projects_delegate.get());

  m_recent_projects_delegate->setIconSize(QSize(64, 64));
  m_recent_projects_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_recent_projects_delegate->setSpacing(10, 15);

  m_search_proxy_model->setFilterRole(
      RecentProjectListModel::Role::ProjectNameRole);
}

void NoProjectWindow::initConnections() {
  connect(m_ui->m_open_button, &QPushButton::clicked, this,
          &NoProjectWindow::openProject);
  connect(m_ui->m_new_project_button, &QPushButton::clicked, this,
          &NoProjectWindow::createProject);

  connect(m_ui->m_projects_list_view, &QListView::activated, this,
          &NoProjectWindow::openRecentProject);
  connect(m_ui->m_search_project_edit, &QLineEdit::textChanged, this,
          &NoProjectWindow::searchRecentProject);
}

void NoProjectWindow::retranslateUi() { m_ui->retranslateUi(this); }