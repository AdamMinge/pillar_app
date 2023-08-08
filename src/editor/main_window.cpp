/* ----------------------------------- Local -------------------------------- */
#include "main_window.h"

#include "about_dialog.h"
#include "project/no_project_window.h"
#include "project/project_window.h"
#include "settings/settings_dialog.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/action_manager.h>
#include <egnite/preferences_manager.h>
#include <egnite/project/project.h>
#include <egnite/project/project_manager.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/action/action.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences {
  egnite::Preference<QByteArray> main_window_geometry =
      egnite::Preference<QByteArray>("main_window/geometry");
  egnite::Preference<QByteArray> main_window_state =
      egnite::Preference<QByteArray>("main_window/state");
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_preferences(new Preferences),
      m_stacked_widget(new QStackedWidget(this)),
      m_project_window(nullptr),
      m_no_project_window(nullptr),
      m_about_action(utils::createActionWithShortcut(QKeySequence{}, this)),
      m_settings_action(utils::createActionWithShortcut(
          Qt::CTRL | Qt::ALT | Qt::Key_S, this)),
      m_exit_action(
          utils::createActionWithShortcut(QKeySequence::Close, this)) {
  registerActions();

  initUi();
  initConnections();

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent *event) {
  if (auto current_widget = m_stacked_widget->currentWidget();
      current_widget->close()) {
    writeSettings();
    event->accept();
  } else {
    event->ignore();
  }
}

void MainWindow::changeEvent(QEvent *event) {
  QMainWindow::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void MainWindow::registerActions() {
  egnite::ActionManager::getInstance().registerAction(m_about_action, "about");
  egnite::ActionManager::getInstance().registerAction(m_settings_action,
                                                      "settings");
  egnite::ActionManager::getInstance().registerAction(m_exit_action, "exit");
}

void MainWindow::initUi() {
  m_ui->setupUi(this);

  m_no_project_window = new NoProjectWindow(this);
  m_project_window = new ProjectWindow(this);

  m_stacked_widget->addWidget(m_project_window);
  m_stacked_widget->addWidget(m_no_project_window);

  currentProjectChanged(
      egnite::ProjectManager::getInstance().getCurrentProject());

  setCentralWidget(m_stacked_widget);
}

void MainWindow::initConnections() {
  connect(m_about_action, &QAction::triggered, this, &MainWindow::openAbout);
  connect(m_settings_action, &QAction::triggered, this,
          &MainWindow::openSettings);
  connect(m_exit_action, &QAction::triggered, this, &MainWindow::close);

  connect(&egnite::ProjectManager::getInstance(),
          &egnite::ProjectManager::currentProjectChanged, this,
          &MainWindow::currentProjectChanged);
}

void MainWindow::writeSettings() {
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();

  m_no_project_window->writeSettings();
  m_project_window->writeSettings();
}

void MainWindow::readSettings() {
  auto window_geometry = m_preferences->main_window_geometry.get();
  auto window_state = m_preferences->main_window_state.get();

  if (!window_geometry.isNull()) restoreGeometry(window_geometry);
  if (!window_state.isNull()) restoreState(window_state);

  m_no_project_window->readSettings();
  m_project_window->readSettings();
}

void MainWindow::retranslateUi() {
  m_ui->retranslateUi(this);

  m_about_action->setText(tr("&About..."));
  m_about_action->setWhatsThis(tr("About Application"));
  m_settings_action->setText(tr("&Settings..."));
  m_settings_action->setWhatsThis(tr("Settings Application"));
  m_exit_action->setText(tr("&Exit"));
  m_exit_action->setWhatsThis(tr("Exit Application"));
}

void MainWindow::openSettings() {
  SettingsDialog::exec(QUrl("settings:GeneralSettingsWidget"));
}

void MainWindow::openAbout() { AboutDialog::show(QUrl{}, this); }

void MainWindow::currentProjectChanged(egnite::Project *project) {
  auto prev_current_widget = m_stacked_widget->currentWidget();
  auto next_current_widget = project
                                 ? static_cast<QWidget *>(m_project_window)
                                 : static_cast<QWidget *>(m_no_project_window);

  disconnect(prev_current_widget, &QWidget::windowTitleChanged, this,
             &MainWindow::updateWindowTitle);
  connect(next_current_widget, &QWidget::windowTitleChanged, this,
          &MainWindow::updateWindowTitle);

  m_stacked_widget->setCurrentWidget(next_current_widget);

  updateWindowTitle();
}

void MainWindow::updateWindowTitle() {
  auto current_widget = m_stacked_widget->currentWidget();

  setWindowTitle(current_widget->windowTitle());
  setWindowFilePath(current_widget->windowFilePath());
  setWindowModified(current_widget->isWindowModified());
}
