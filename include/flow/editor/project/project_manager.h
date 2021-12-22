#ifndef FLOW_PROJECT_MANAGER_H
#define FLOW_PROJECT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class Project;

class ProjectManager : public QObject
{
  Q_OBJECT

public:
  static ProjectManager &getInstance();
  static void deleteInstance();

public:
  ~ProjectManager() override;

  void addProject(std::unique_ptr<Project> project);
  void insertProject(int index, std::unique_ptr<Project> project);

  void removeProject(int index);
  void removeAllProjects();

  [[nodiscard]] Project *getProject(int index) const;
  [[nodiscard]] Project *getCurrentProject() const;

  [[nodiscard]] int findProject(Project *project) const;
  [[nodiscard]] int findProject(const QString &file_name) const;

  void switchToProject(int index);
  void switchToProject(Project *project);
  bool switchToProject(const QString &file_name);

  bool loadProject(const QString &file_name);

Q_SIGNALS:
  void currentProjectChanged(Project *project);

protected:
  explicit ProjectManager();

private:
  static QScopedPointer<ProjectManager> m_instance;

  std::vector<std::unique_ptr<Project>> m_projects;
  Project *m_current_project;
};

#endif//FLOW_PROJECT_MANAGER_H
