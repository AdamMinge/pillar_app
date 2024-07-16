#ifndef PROJECT_DOCK_H
#define PROJECT_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QScopedPointer>
/* -------------------------------------------------------------------------- */

class QAbstractFileIconProvider;
class QFileSystemModel;
class QTreeView;

namespace pillar {
class Project;
}

namespace qtils {
class FileSystemProxyModel;
}

class ProjectDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit ProjectDock(QWidget *parent = nullptr);
  ~ProjectDock() override;

  void setProject(pillar::Project *project);
  [[nodiscard]] pillar::Project *getProject() const;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private Q_SLOTS:
  void openFile(const QModelIndex &index);
  void removeFile(const QModelIndex &index);
  void renameFile(const QModelIndex &index);
  void newDirectory(const QModelIndex &index);

  void openContextMenu(const QPoint &position);
  void openDocument(const QModelIndex &index);

 private:
  pillar::Project *m_current_project;

  QTreeView *m_view;
  QFileSystemModel *m_model;
  qtils::FileSystemProxyModel *m_proxy;

  QScopedPointer<QAbstractFileIconProvider> m_icon_provider;
};

#endif  // PROJECT_DOCK_H
