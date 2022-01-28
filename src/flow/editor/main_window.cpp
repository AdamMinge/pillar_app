/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/about_dialog.h"
#include "flow/editor/action_manager.h"
#include "flow/editor/language_manager.h"
#include "flow/editor/main_window.h"
#include "flow/editor/preferences_manager.h"
#include "flow/editor/project/no_project_window.h"
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_manager.h"
#include "flow/editor/project/project_window.h"
#include "flow/editor/settings_dialog.h"
#include "flow/editor/style_manager.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences {
  Preference<QByteArray> main_window_geometry = Preference<QByteArray>("main_window/geometry");
  Preference<QByteArray> main_window_state = Preference<QByteArray>("main_window/state");
  Preference<QLocale> application_language = Preference<QLocale>("application/language");
  Preference<QString> application_style = Preference<QString>("application/style");
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_preferences(new Preferences),
      m_stacked_widget(new QStackedWidget(this)),
      m_project_window(nullptr),
      m_no_project_window(nullptr),
      m_about_action(new QAction(tr("&About..."), this)),
      m_settings_action(new QAction(tr("&Settings..."), this)),
      m_exit_action(new QAction(tr("&Exit"), this))
{
  getActionManager().registerAction(m_about_action, "about");
  getActionManager().registerAction(m_settings_action, "settings");
  getActionManager().registerAction(m_exit_action, "exit");

  initUi();
  initConnections();

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow() = default;

LanguageManager &MainWindow::getLanguageManager() const// NOLINT(readability-convert-member-functions-to-static)
{
  return LanguageManager::getInstance();
}

ProjectManager &MainWindow::getProjectManager() const// NOLINT(readability-convert-member-functions-to-static)
{
  return ProjectManager::getInstance();
}

StyleManager &MainWindow::getStyleManager() const// NOLINT(readability-convert-member-functions-to-static)
{
  return StyleManager::getInstance();
}

ActionManager &MainWindow::getActionManager() const// NOLINT(readability-convert-member-functions-to-static)
{
  return ActionManager::getInstance();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (auto current_widget = m_stacked_widget->currentWidget(); current_widget->close())
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
  connect(m_settings_action, &QAction::triggered, this, &MainWindow::openSettings);
  connect(m_exit_action, &QAction::triggered, this, &MainWindow::close);

  connect(&getProjectManager(), &ProjectManager::currentProjectChanged, this, &MainWindow::currentProjectChanged);
}

void MainWindow::writeSettings()
{
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();
  m_preferences->application_language = getLanguageManager().getCurrentLanguage();
  m_preferences->application_style = getStyleManager().getCurrentStyle();

  m_no_project_window->writeSettings();
  m_project_window->writeSettings();
}

void MainWindow::readSettings()
{
  auto window_geometry = m_preferences->main_window_geometry.get();
  auto window_state = m_preferences->main_window_state.get();

  if (!window_geometry.isNull()) restoreGeometry(window_geometry);
  if (!window_state.isNull()) restoreState(window_state);

  auto application_language = m_preferences->application_language.get();
  auto application_style = m_preferences->application_style.get();

  auto languages = getLanguageManager().getAvailableLanguages();
  if (languages.contains(application_language))
    getLanguageManager().setLanguage(application_language);
  else if (languages.contains(QLocale::system()))
    getLanguageManager().setLanguage(QLocale::system());

  if (!application_style.isEmpty())
    getStyleManager().setStyle(application_style);

  m_no_project_window->readSettings();
  m_project_window->readSettings();
}

void MainWindow::retranslateUi()
{
  m_ui->retranslateUi(this);

  m_about_action->setText(tr("&About..."));
  m_settings_action->setText(tr("&Settings..."));
  m_exit_action->setText(tr("&Exit"));
}

void MainWindow::openSettings()
{
  if (!m_settings_dialog)
  {
    m_settings_dialog = new SettingsDialog(this);
    m_settings_dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  m_settings_dialog->show();
  m_settings_dialog->activateWindow();
  m_settings_dialog->raise();
}

void MainWindow::openAbout()
{
  if (!m_about_dialog)
  {
    m_about_dialog = new AboutDialog(this);
    m_about_dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  m_about_dialog->show();
  m_about_dialog->activateWindow();
  m_about_dialog->raise();
}

void MainWindow::currentProjectChanged(api::IProject *project)
{
  auto prev_current_widget = m_stacked_widget->currentWidget();
  auto next_current_widget = project ? static_cast<QWidget *>(m_project_window) : static_cast<QWidget *>(m_no_project_window);

  disconnect(prev_current_widget, &QWidget::windowTitleChanged, this, &MainWindow::updateWindowTitle);
  connect(next_current_widget, &QWidget::windowTitleChanged, this, &MainWindow::updateWindowTitle);

  m_stacked_widget->setCurrentWidget(next_current_widget);

  updateWindowTitle();
}

void MainWindow::updateWindowTitle()
{
  auto current_widget = m_stacked_widget->currentWidget();

  setWindowTitle(current_widget->windowTitle());
  setWindowFilePath(current_widget->windowFilePath());
}
