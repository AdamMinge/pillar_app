#ifndef FLOW_NO_PROJECT_WINDOW_H
#define FLOW_NO_PROJECT_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NoProjectWindow;
}

class PreferencesManager;
class ProjectManager;

class RecentProjectListModel;
class RecentProjectListDelegate;

class NoProjectWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit NoProjectWindow(QWidget *parent = nullptr);
  ~NoProjectWindow() override;

protected:
  void changeEvent(QEvent *event) override;

  [[nodiscard]] static PreferencesManager &getPreferencesManager();
  [[nodiscard]] static ProjectManager &getProjectManager();

private Q_SLOTS:
  void openProject();
  void createProject();

  void openRecentProject(const QModelIndex &index);
  void searchRecentProject(const QString &search);

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::NoProjectWindow> m_ui;
  QScopedPointer<RecentProjectListModel> m_recent_projects_model;
  QScopedPointer<RecentProjectListDelegate> m_recent_projects_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

#endif//FLOW_NO_PROJECT_WINDOW_H
