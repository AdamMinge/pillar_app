/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project_manager.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMessageBox>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/project/project.h>
/* -------------------------------------------------------------------------- */

QScopedPointer<ProjectManager> ProjectManager::m_instance =
  QScopedPointer<ProjectManager>(nullptr);

ProjectManager &ProjectManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new ProjectManager);

  return *m_instance;
}

void ProjectManager::deleteInstance() { m_instance.reset(nullptr); }

ProjectManager::ProjectManager() : m_current_project(nullptr) {}

ProjectManager::~ProjectManager() = default;

void ProjectManager::addProject(std::unique_ptr<flow::project::Project> project)
{
  insertProject(static_cast<int>(m_projects.size()), std::move(project));
}

void ProjectManager::insertProject(
  int index, std::unique_ptr<flow::project::Project> project)
{
  Q_ASSERT(project);
  auto project_ptr = project.get();
  m_projects.insert(m_projects.begin() + index, std::move(project));

  switchToProject(project_ptr);
}

void ProjectManager::removeProject(int index)
{
  auto project_to_remove = getProject(index);
  Q_ASSERT(project_to_remove);

  auto removed_project_iter = std::remove_if(
    m_projects.begin(), m_projects.end(), [&project_to_remove](auto &project) {
      return project.get() == project_to_remove;
    });

  if (project_to_remove == m_current_project) switchToProject(nullptr);

  m_projects.erase(removed_project_iter, m_projects.end());
}

void ProjectManager::removeAllProjects()
{
  while (!m_projects.empty()) removeProject(0);
}

flow::project::Project *ProjectManager::getProject(int index) const
{
  if (index < m_projects.size() && index >= 0)
    return m_projects.at(index).get();

  return nullptr;
}

flow::project::Project *ProjectManager::getCurrentProject() const
{
  return m_current_project;
}

int ProjectManager::findProject(flow::project::Project *project) const
{
  auto found = std::find_if(
    m_projects.begin(), m_projects.end(), [project](auto &current_project) {
      return current_project.get() == project;
    });

  if (found == m_projects.end()) return -1;

  return static_cast<int>(std::distance(m_projects.begin(), found));
}

int ProjectManager::findProject(const QString &file_name) const
{
  auto found = std::find_if(
    m_projects.begin(), m_projects.end(), [&file_name](auto &current_project) {
      return current_project->getFileName() == file_name;
    });

  if (found == m_projects.end()) return -1;

  return static_cast<int>(std::distance(m_projects.begin(), found));
}

void ProjectManager::switchToProject(int index)
{
  auto found_project = getProject(index);
  Q_ASSERT(found_project);
  return switchToProject(found_project);
}

void ProjectManager::switchToProject(flow::project::Project *project)
{
  if (m_current_project == project) return;

  m_current_project = project;
  Q_EMIT currentProjectChanged(m_current_project);
}

bool ProjectManager::switchToProject(const QString &file_name)
{
  auto index = findProject(file_name);
  auto found_project = getProject(index);
  if (!found_project) return false;

  switchToProject(found_project);
  return true;
}

bool ProjectManager::loadProject(const QString &file_name, QString *error)
{
  if (switchToProject(file_name)) return true;

  auto project = flow::project::Project::load(file_name, nullptr, error);
  if (!project) return false;

  addProject(std::move(project));
  return true;
}
