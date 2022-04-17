/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/about_dialog.h"
#include "flow/editor/action_manager.h"
#include "flow/editor/language_manager.h"
#include "flow/editor/main_window.h"
#include "flow/editor/plugin_manager.h"
#include "flow/editor/preferences_manager.h"
#include "flow/editor/project/no_project_window.h"
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_manager.h"
#include "flow/editor/project/project_window.h"
#include "flow/editor/settings/settings_dialog.h"
#include "flow/editor/style_manager.h"
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/action/action.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences {
  Preference<QByteArray> main_window_geometry =
    Preference<QByteArray>("main_window/geometry");
  Preference<QByteArray> main_window_state =
    Preference<QByteArray>("main_window/state");
  Preference<QLocale> application_language =
    Preference<QLocale>("application/language");
  Preference<QString> application_style =
    Preference<QString>("application/style");
  Preference<QStringList> application_enabled_plugins =
    Preference<QStringList>("application/denabled_plugins");
  PreferenceContainer<QKeySequence> application_shortcuts =
    PreferenceContainer<QKeySequence>("application/shortcuts");
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow),
      m_preferences(new Preferences),
      m_stacked_widget(new QStackedWidget(this)), m_project_window(nullptr),
      m_no_project_window(nullptr),
      m_about_action(utils::createActionWithShortcut(QKeySequence{}, this)),
      m_settings_action(
        utils::createActionWithShortcut(Qt::CTRL | Qt::ALT | Qt::Key_S, this)),
      m_exit_action(utils::createActionWithShortcut(QKeySequence::Close, this))
{
  registerActions();

  initUi();
  initConnections();

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow() = default;

LanguageManager &MainWindow::
  getLanguageManager()// NOLINT(readability-convert-member-functions-to-static)
  const
{
  return LanguageManager::getInstance();
}

ProjectManager &MainWindow::
  getProjectManager()// NOLINT(readability-convert-member-functions-to-static)
  const
{
  return ProjectManager::getInstance();
}

PluginManager &MainWindow::
  getPluginManager()// NOLINT(readability-convert-member-functions-to-static)
  const
{
  return PluginManager::getInstance();
}

StyleManager &MainWindow::
  getStyleManager()// NOLINT(readability-convert-member-functions-to-static)
  const
{
  return StyleManager::getInstance();
}

ActionManager &MainWindow::
  getActionManager()// NOLINT(readability-convert-member-functions-to-static)
  const
{
  return ActionManager::getInstance();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (auto current_widget = m_stacked_widget->currentWidget();
      current_widget->close())
  {
    writeSettings();
    event->accept();
  } else
  {
    event->ignore();
  }
}

void MainWindow::changeEvent(QEvent *event)
{
  QMainWindow::changeEvent(event);
  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void MainWindow::registerActions()
{
  getActionManager().registerAction(m_about_action, "about");
  getActionManager().registerAction(m_settings_action, "settings");
  getActionManager().registerAction(m_exit_action, "exit");
}

void MainWindow::initUi()
{
  m_ui->setupUi(this);

  m_no_project_window = new NoProjectWindow(this);
  m_project_window = new ProjectWindow(this);

  m_stacked_widget->addWidget(m_project_window);
  m_stacked_widget->addWidget(m_no_project_window);

  currentProjectChanged(getProjectManager().getCurrentProject());

  setCentralWidget(m_stacked_widget);
}

void MainWindow::initConnections()
{
  connect(m_about_action, &QAction::triggered, this, &MainWindow::openAbout);
  connect(
    m_settings_action, &QAction::triggered, this, &MainWindow::openSettings);
  connect(m_exit_action, &QAction::triggered, this, &MainWindow::close);

  connect(
    &getProjectManager(), &ProjectManager::currentProjectChanged, this,
    &MainWindow::currentProjectChanged);
}

void MainWindow::writePlugins()
{
  auto enabled_plugins = QStringList{};
  for (const auto plugin : getPluginManager().getDynamicPlugins())
  {
    if (plugin->isEnabled()) enabled_plugins << plugin->getFileName();
  }

  m_preferences->application_enabled_plugins = enabled_plugins;
}

void MainWindow::writeSettings()
{
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();

  writePlugins();
  writeLanguage();
  writeStyle();
  writeShortcuts();

  m_no_project_window->writeSettings();
  m_project_window->writeSettings();
}

void MainWindow::writeLanguage()
{
  m_preferences->application_language =
    getLanguageManager().getCurrentLanguage();
}

void MainWindow::writeStyle()
{
  m_preferences->application_style = getStyleManager().getCurrentStyle();
}

void MainWindow::writeShortcuts()
{
  const auto actions_id = getActionManager().getActionsId();
  for (const auto &action_id : actions_id)
  {
    auto action = getActionManager().findAction(action_id);
    m_preferences->application_shortcuts.set(action_id, action->shortcut());
  }
}

void MainWindow::readSettings()
{
  auto window_geometry = m_preferences->main_window_geometry.get();
  auto window_state = m_preferences->main_window_state.get();

  if (!window_geometry.isNull()) restoreGeometry(window_geometry);
  if (!window_state.isNull()) restoreState(window_state);

  readPlugins();
  readLanguage();
  readStyle();
  readShortcuts();

  m_no_project_window->readSettings();
  m_project_window->readSettings();
}

void MainWindow::readPlugins()
{
  const auto enabled_plugins = m_preferences->application_enabled_plugins.get();

  for (getPluginManager().loadPlugins();
       auto plugin : getPluginManager().getPlugins())
  {
    if (enabled_plugins.contains(plugin->getFileName())) plugin->enable();
  }
}

void MainWindow::readLanguage()
{
  const auto application_language = m_preferences->application_language.get();

  auto languages = getLanguageManager().getAvailableLanguages();
  if (languages.contains(application_language))
    getLanguageManager().setLanguage(application_language);
  else if (languages.contains(QLocale::system()))
    getLanguageManager().setLanguage(QLocale::system());
}

void MainWindow::readStyle()
{
  auto application_style = m_preferences->application_style.get();
  if (!application_style.isEmpty())
    getStyleManager().setStyle(application_style);
}

void MainWindow::readShortcuts()
{
  const auto actions_id = getActionManager().getActionsId();
  for (const auto &action_id : actions_id)
  {
    if (m_preferences->application_shortcuts.contains(action_id))
    {
      auto shortcut = m_preferences->application_shortcuts.get(action_id);
      getActionManager().setCustomShortcut(action_id, shortcut);
    }
  }
}

void MainWindow::retranslateUi()
{
  m_ui->retranslateUi(this);

  m_about_action->setText(tr("&About..."));
  m_about_action->setWhatsThis(tr("About Application"));
  m_settings_action->setText(tr("&Settings..."));
  m_settings_action->setWhatsThis(tr("Settings Application"));
  m_exit_action->setText(tr("&Exit"));
  m_exit_action->setWhatsThis(tr("Exit Application"));
}

void MainWindow::openSettings() { SettingsDialog::open(QUrl{}, this); }

void MainWindow::openAbout() { AboutDialog::open(QUrl{}, this); }

void MainWindow::currentProjectChanged(api::project::IProject *project)
{
  auto prev_current_widget = m_stacked_widget->currentWidget();
  auto next_current_widget = project
                               ? static_cast<QWidget *>(m_project_window)
                               : static_cast<QWidget *>(m_no_project_window);

  disconnect(
    prev_current_widget, &QWidget::windowTitleChanged, this,
    &MainWindow::updateWindowTitle);
  connect(
    next_current_widget, &QWidget::windowTitleChanged, this,
    &MainWindow::updateWindowTitle);

  m_stacked_widget->setCurrentWidget(next_current_widget);

  updateWindowTitle();
}

void MainWindow::updateWindowTitle()
{
  auto current_widget = m_stacked_widget->currentWidget();

  setWindowTitle(current_widget->windowTitle());
  setWindowFilePath(current_widget->windowFilePath());
}
