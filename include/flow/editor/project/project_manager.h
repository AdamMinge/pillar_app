#ifndef FLOW_PROJECT_MANAGER_H
#define FLOW_PROJECT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

namespace flow::project
{
  class Project;
}

class ProjectManager : public QObject
{
  Q_OBJECT

public:
  static ProjectManager &getInstance();
  static void deleteInstance();

public:
  ~ProjectManager() override;

  void addProject(std::unique_ptr<flow::project::Project> project);
  void
  insertProject(int index, std::unique_ptr<flow::project::Project> project);

  void removeProject(int index);
  void removeAllProjects();

  [[nodiscard]] flow::project::Project *getProject(int index) const;
  [[nodiscard]] flow::project::Project *getCurrentProject() const;

  [[nodiscard]] int findProject(flow::project::Project *project) const;
  [[nodiscard]] int findProject(const QString &file_name) const;

  void switchToProject(int index);
  void switchToProject(flow::project::Project *project);
  bool switchToProject(const QString &file_name);

  bool loadProject(const QString &file_name, QString *error = nullptr);

Q_SIGNALS:
  void currentProjectChanged(flow::project::Project *project);

protected:
  explicit ProjectManager();

private:
  static QScopedPointer<ProjectManager> m_instance;

  std::vector<std::unique_ptr<flow::project::Project>> m_projects;
  flow::project::Project *m_current_project;
};

#endif//FLOW_PROJECT_MANAGER_H
