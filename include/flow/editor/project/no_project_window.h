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

class ProjectManager;

class RecentProjectListModel;
class RecentProjectListDelegate;

class NoProjectWindow : public QMainWindow
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NoProjectWindow(QWidget *parent = nullptr);
  ~NoProjectWindow() override;

  void writeSettings();
  void readSettings();

protected:
  void changeEvent(QEvent *event) override;

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
  QScopedPointer<Preferences> m_preferences;

  QScopedPointer<RecentProjectListModel> m_recent_projects_model;
  QScopedPointer<RecentProjectListDelegate> m_recent_projects_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

#endif//FLOW_NO_PROJECT_WINDOW_H
