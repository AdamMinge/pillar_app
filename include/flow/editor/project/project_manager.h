#ifndef FLOW_PROJECT_MANAGER_H
#define FLOW_PROJECT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

namespace api
{
  class IProject;
}

class ProjectManager : public QObject
{
  Q_OBJECT

public:
  static ProjectManager &getInstance();
  static void deleteInstance();

public:
  ~ProjectManager() override;

  void addProject(std::unique_ptr<api::project::IProject> project);
  void
  insertProject(int index, std::unique_ptr<api::project::IProject> project);

  void removeProject(int index);
  void removeAllProjects();

  [[nodiscard]] api::project::IProject *getProject(int index) const;
  [[nodiscard]] api::project::IProject *getCurrentProject() const;

  [[nodiscard]] int findProject(api::project::IProject *project) const;
  [[nodiscard]] int findProject(const QString &file_name) const;

  void switchToProject(int index);
  void switchToProject(api::project::IProject *project);
  bool switchToProject(const QString &file_name);

  bool loadProject(const QString &file_name, QString *error = nullptr);

Q_SIGNALS:
  void currentProjectChanged(api::project::IProject *project);

protected:
  explicit ProjectManager();

private:
  static QScopedPointer<ProjectManager> m_instance;

  std::vector<std::unique_ptr<api::project::IProject>> m_projects;
  api::project::IProject *m_current_project;
};

#endif//FLOW_PROJECT_MANAGER_H
