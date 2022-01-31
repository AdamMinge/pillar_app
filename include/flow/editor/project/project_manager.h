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

  void addProject(std::unique_ptr<api::IProject> project);
  void insertProject(int index, std::unique_ptr<api::IProject> project);

  void removeProject(int index);
  void removeAllProjects();

  [[nodiscard]] api::IProject *getProject(int index) const;
  [[nodiscard]] api::IProject *getCurrentProject() const;

  [[nodiscard]] int findProject(api::IProject *project) const;
  [[nodiscard]] int findProject(const QString &file_name) const;

  void switchToProject(int index);
  void switchToProject(api::IProject *project);
  bool switchToProject(const QString &file_name);

  bool loadProject(const QString &file_name, QString *error = nullptr);

Q_SIGNALS:
  void currentProjectChanged(api::IProject *project);

protected:
  explicit ProjectManager();

private:
  static QScopedPointer<ProjectManager> m_instance;

  std::vector<std::unique_ptr<api::IProject>> m_projects;
  api::IProject *m_current_project;
};

#endif//FLOW_PROJECT_MANAGER_H
