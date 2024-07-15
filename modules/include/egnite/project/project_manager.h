#ifndef EGNITE_PROJECT_MANAGER_H
#define EGNITE_PROJECT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class Project;

class LIB_EGNITE_API ProjectManager : public QObject {
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

  bool loadProject(const QString &file_name, QString *error = nullptr);

 Q_SIGNALS:
  void currentProjectChanged(egnite::Project *project);

 protected:
  explicit ProjectManager();

 private:
  static std::unique_ptr<ProjectManager> m_instance;

  std::vector<std::unique_ptr<Project>> m_projects;
  Project *m_current_project;
};

}  // namespace egnite

#endif  // EGNITE_PROJECT_MANAGER_H
