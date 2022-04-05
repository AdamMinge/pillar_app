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

namespace api::project
{
  class IProject;
}

class LanguageManager;
class ProjectManager;
class PluginManager;
class ActionManager;
class StyleManager;

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

  [[nodiscard]] LanguageManager &getLanguageManager() const;
  [[nodiscard]] ProjectManager &getProjectManager() const;
  [[nodiscard]] PluginManager &getPluginManager() const;
  [[nodiscard]] StyleManager &getStyleManager() const;
  [[nodiscard]] ActionManager &getActionManager() const;

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

  void readSettings();
  void readPlugins();
  void readLanguage();
  void readStyle();

  void retranslateUi();

private Q_SLOTS:
  void openSettings();
  void openAbout();

  void currentProjectChanged(api::project::IProject *project);

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
