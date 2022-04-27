#ifndef FLOW_MAIN_WINDOW_H
#define FLOW_MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
#include <QPointer>
#include <QStackedWidget>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class MainWindow;
}

namespace flow::project
{
  class Project;
}// namespace flow::project

class ProjectWindow;
class NoProjectWindow;

class MainWindow final : public QMainWindow
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private:
  void registerActions();

  void initUi();
  void initConnections();

  void writeSettings();
  void writePlugins();
  void writeLanguage();
  void writeStyle();
  void writeShortcuts();

  void readSettings();
  void readPlugins();
  void readLanguage();
  void readStyle();
  void readShortcuts();

  void retranslateUi();

private Q_SLOTS:
  void openSettings();
  void openAbout();

  void currentProjectChanged(flow::project::Project *project);

  void updateWindowTitle();

private:
  QScopedPointer<Ui::MainWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;

  QStackedWidget *m_stacked_widget;
  ProjectWindow *m_project_window;
  NoProjectWindow *m_no_project_window;

  QAction *m_about_action;
  QAction *m_settings_action;
  QAction *m_exit_action;
};

#endif//FLOW_MAIN_WINDOW_H
