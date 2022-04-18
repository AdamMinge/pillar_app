/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/action_manager.h"
#include "flow/editor/console_dock.h"
#include "flow/editor/document/document_manager.h"
#include "flow/editor/document/flow/flow_editor.h"
#include "flow/editor/document/new_document_dialog.h"
#include "flow/editor/format_helper.h"
#include "flow/editor/issue_dock.h"
#include "flow/editor/preferences_manager.h"
#include "flow/editor/project/new_project_dialog.h"
#include "flow/editor/project/project.h"
#include "flow/editor/project/project_dock.h"
#include "flow/editor/project/project_manager.h"
#include "flow/editor/project/project_window.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/api/document/document_format.h>
#include <flow/modules/api/project/project_format.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/action/action.h>
#include <flow/utils/qt/dialog/dialog_with_toggle_view.h>
#include <flow/utils/qt/dialog/extended_file_dialog.h>
#include <flow/utils/qt/dpi/dpi_info.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_project_window.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------- adjustMenuSize --------------------------- */

void adjustMenuSize(QObject *object)
{
  if (auto menu = qobject_cast<QMenu *>(object); menu)
  {
    auto max_width = 0;
    auto extra_width = utils::QtDpiInfo::dpiScaled(55);
    for (auto action : menu->actions())
    {
      const auto fontMetrics = QFontMetrics(action->font());
      auto width = fontMetrics.horizontalAdvance(action->text());

      if (auto child_menu = action->menu(); child_menu)
      {
        adjustMenuSize(child_menu);
        width += utils::QtDpiInfo::dpiScaled(5);
      }

      if (!action->shortcut().isEmpty())
        extra_width = utils::QtDpiInfo::dpiScaled(120);

      if (max_width < width) max_width = width;
    }

    menu->setMinimumWidth(max_width + extra_width);
  } else
  {
    for (auto child_menu :
         object->findChildren<QMenu *>(QString{}, Qt::FindDirectChildrenOnly))
      adjustMenuSize(child_menu);
  }
}

/* -------------------------------- Preferences ----------------------------- */

struct ProjectWindow::Preferences {
  Preference<QByteArray> project_window_geometry =
    Preference<QByteArray>("project_window/geometry");
  Preference<QByteArray> project_window_state =
    Preference<QByteArray>("project_window/state");
};

/* ------------------------------- ProjectWindow ---------------------------- */

ProjectWindow::ProjectWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::ProjectWindow),
      m_preferences(new Preferences), m_project_dock(new ProjectDock(this)),
      m_console_dock(new ConsoleDock(this)), m_issue_dock(new IssueDock(this)),
      m_project_menu(new QMenu(this)),
      m_new_project_action(
        utils::createActionWithShortcut(QKeySequence{}, this)),
      m_open_project_action(
        utils::createActionWithShortcut(QKeySequence{}, this)),
      m_open_recent_project_menu(new QMenu(this)),
      m_clear_recent_projects_action(
        utils::createActionWithShortcut(QKeySequence{}, this)),
      m_close_project_action(
        utils::createActionWithShortcut(QKeySequence{}, this)),
      m_document_menu(new QMenu(this)),
      m_new_document_action(
        utils::createActionWithShortcut(QKeySequence::New, this)),
      m_open_document_action(
        utils::createActionWithShortcut(QKeySequence::Open, this)),
      m_close_document_action(
        utils::createActionWithShortcut(QKeySequence{}, this)),
      m_save_document_action(
        utils::createActionWithShortcut(QKeySequence::Save, this)),
      m_save_document_as_action(
        utils::createActionWithShortcut(QKeySequence::SaveAs, this)),
      m_save_all_documents_action(
        utils::createActionWithShortcut(QKeySequence{}, this)),
      m_edit_menu(new QMenu(this)),
      m_cut_action(utils::createActionWithShortcut(QKeySequence::Cut, this)),
      m_copy_action(utils::createActionWithShortcut(QKeySequence::Copy, this)),
      m_paste_action(
        utils::createActionWithShortcut(QKeySequence::Paste, this)),
      m_delete_action(
        utils::createActionWithShortcut(QKeySequence::Delete, this)),
      m_view_menu(new QMenu(this)), m_views_and_toolbars_menu(new QMenu(this)),
      m_help_menu(new QMenu(this))
{
  auto undoGroup = getDocumentManager().getUndoGroup();
  m_undo_action = undoGroup->createUndoAction(this, tr("&Undo"));
  m_undo_action->setShortcut(QKeySequence::Undo);
  m_redo_action = undoGroup->createRedoAction(this, tr("&Redo"));
  m_redo_action->setShortcut(QKeySequence::Redo);

  registerActions();

  initUi();
  initConnections();

  updateActions();
  updateWindowTitle();
  updateRecentProjectFiles();

  retranslateUi();
}

ProjectWindow::~ProjectWindow() = default;

void ProjectWindow::closeEvent(QCloseEvent *event)
{
  if (confirmAllSave())
  {
    event->accept();
  } else
  {
    event->ignore();
  }
}

void ProjectWindow::changeEvent(QEvent *event)
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

DocumentManager &ProjectWindow::getDocumentManager()
{
  return DocumentManager::getInstance();
}

ProjectManager &ProjectWindow::getProjectManager()
{
  return ProjectManager::getInstance();
}

ActionManager &ProjectWindow::getActionManager()
{
  return ActionManager::getInstance();
}

PreferencesManager &ProjectWindow::getPreferencesManager()
{
  return PreferencesManager::getInstance();
}

void ProjectWindow::documentChanged(api::document::IDocument *document)
{
  updateActions();
  updateRecentProjectFiles();
}

void ProjectWindow::projectChanged(api::project::IProject *project)
{
  m_project_dock->setProject(project);
  updateWindowTitle();
}

bool ProjectWindow::confirmSave(api::document::IDocument *document)
{
  if (!document || !document->isModified()) return true;

  getDocumentManager().switchToDocument(document);

  auto ret = QMessageBox::warning(
    this, tr("Unsaved Changes"),
    tr("There are unsaved changes. Do you want to save now?"),
    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (ret)
  {
    case QMessageBox::Save:
      return saveDocument(document);
    case QMessageBox::Discard:
      return true;
    case QMessageBox::Cancel:
    default:
      return false;
  }
}

bool ProjectWindow::confirmAllSave()
{
  for (const auto &document : getDocumentManager().getDocuments())
    if (!confirmSave(document.get())) return false;

  return true;
}

void ProjectWindow::updateActions()
{
  auto document_editor = getDocumentManager().getCurrentEditor();
  auto current_document = getDocumentManager().getCurrentDocument();

  api::document::IDocumentEditor::StandardActions standard_actions;
  if (document_editor)
    standard_actions = document_editor->getEnabledStandardActions();

  m_close_document_action->setEnabled(current_document);
  m_save_document_action->setEnabled(current_document);
  m_save_document_as_action->setEnabled(current_document);
  m_save_all_documents_action->setEnabled(current_document);

  m_cut_action->setEnabled(
    standard_actions & api::document::IDocumentEditor::CutAction);
  m_copy_action->setEnabled(
    standard_actions & api::document::IDocumentEditor::CopyAction);
  m_paste_action->setEnabled(
    standard_actions & api::document::IDocumentEditor::PasteAction);
  m_delete_action->setEnabled(
    standard_actions & api::document::IDocumentEditor::DeleteAction);
}

void ProjectWindow::updateWindowTitle()
{
  auto current_project = getProjectManager().getCurrentProject();

  const auto project_name =
    current_project ? tr("[*]%1").arg(current_project->getDisplayName())
                    : QString();
  const auto project_file_path =
    current_project ? current_project->getFileName() : QString();

  auto project_is_modified = false;
  for (const auto &document : getDocumentManager().getDocuments())
    project_is_modified |= document->isModified();

  setWindowTitle(project_name);
  setWindowFilePath(project_file_path);
  setWindowModified(project_is_modified);

  Q_EMIT windowTitleChanged(project_name);
}

void ProjectWindow::updateViewsAndToolbarsMenu()
{
  m_views_and_toolbars_menu->clear();

  m_views_and_toolbars_menu->addAction(m_project_dock->toggleViewAction());
  m_views_and_toolbars_menu->addAction(m_console_dock->toggleViewAction());
  m_views_and_toolbars_menu->addAction(m_issue_dock->toggleViewAction());

  if (auto editor = getDocumentManager().getCurrentEditor())
  {
    m_views_and_toolbars_menu->addSeparator();

    auto dockWidgets = editor->getDockWidgets();
    auto dialogWidgets = editor->getDialogWidgets();

    for (auto &dockWidget : dockWidgets)
      m_views_and_toolbars_menu->addAction(dockWidget->toggleViewAction());

    m_views_and_toolbars_menu->addSeparator();

    for (auto &dialogWidget : dialogWidgets)
      m_views_and_toolbars_menu->addAction(dialogWidget->toggleViewAction());
  }

  adjustMenuSize(m_views_and_toolbars_menu);
}

void ProjectWindow::updateRecentProjectFiles()
{
  auto recent_project_files = getPreferencesManager().getRecentProjectFiles();

  for (auto &action : m_open_recent_project_menu->actions())
  {
    if (action != m_clear_recent_projects_action) action->deleteLater();
  }

  for (auto &recent_project_file : recent_project_files)
  {
    auto fileInfo = QFileInfo(recent_project_file);
    if (!fileInfo.exists()) continue;

    auto open_recent_project_action = utils::createActionWithShortcut(
      QKeySequence{}, m_open_recent_project_menu);
    open_recent_project_action->setText(fileInfo.fileName());
    open_recent_project_action->setToolTip(fileInfo.filePath());
    open_recent_project_action->setVisible(true);

    m_open_recent_project_menu->insertAction(
      m_clear_recent_projects_action, open_recent_project_action);

    connect(
      open_recent_project_action, &QAction::triggered, this,
      [this, recent_project_file]() { openProject(recent_project_file); });
  }

  m_open_recent_project_menu->insertSeparator(m_clear_recent_projects_action);

  adjustMenuSize(m_open_recent_project_menu);
}

void ProjectWindow::newProject()
{
  auto new_project_dialog =
    QScopedPointer<NewProjectDialog>(new NewProjectDialog(this));
  if (auto project = new_project_dialog->create(); project)
    switchProject(std::move(project));
}

void ProjectWindow::openProject()
{
  const auto recent_project_files =
    getPreferencesManager().getRecentProjectFiles();
  const auto project_dir =
    recent_project_files.empty() ? QString{} : recent_project_files.last();
  const auto filter =
    FormatHelper<api::project::IProjectFormat>{
      api::IFileFormat::Capability::Read}
      .getFilter();

  const auto file_name = utils::QtExtendedFileDialog::getOpenFileName(
    this, tr("Open Project"), project_dir, filter);

  if (!file_name.isEmpty()) openProject(file_name);
}

bool ProjectWindow::openProject(const QString &file_name)
{
  if (!getProjectManager().switchToProject(file_name))
  {
    QString error;
    auto project = Project::load(file_name, nullptr, &error);
    if (!project)
    {
      QMessageBox::critical(nullptr, tr("Error Opening File"), error);
      return false;
    }

    return switchProject(std::move(project));
  }

  return true;
}

bool ProjectWindow::closeProject()
{
  if (!confirmAllSave()) return false;

  auto project = getProjectManager().getCurrentProject();
  auto project_index = getProjectManager().findProject(project);
  Q_ASSERT(project_index >= 0);

  getDocumentManager().removeAllDocuments();
  getProjectManager().removeProject(project_index);

  return true;
}

void ProjectWindow::newDocument()
{
  auto new_document_dialog =
    QScopedPointer<NewDocumentDialog>(new NewDocumentDialog(this));
  if (auto document = new_document_dialog->create(); document)
    getDocumentManager().addDocument(std::move(document));
}

void ProjectWindow::openDocument()
{
  const auto project = getProjectManager().getCurrentProject();
  const auto project_dir =
    QFileInfo(project->getFileName()).absoluteDir().absolutePath();
  const auto filter =
    FormatHelper<api::document::IDocumentFormat>{
      api::IFileFormat::Capability::Read}
      .getFilter();

  const auto file_name = utils::QtExtendedFileDialog::getOpenFileName(
    this, tr("Open Document"), project_dir, filter);

  if (!file_name.isEmpty()) getDocumentManager().loadDocument(file_name);
}

bool ProjectWindow::closeDocument(int index)
{
  auto document = getDocumentManager().getDocument(index);
  if (document)
  {
    if (!confirmSave(document)) return false;

    getDocumentManager().removeDocument(index);
  }

  return true;
}

bool ProjectWindow::closeDocument()
{
  auto current_document = getDocumentManager().getCurrentDocument();
  auto current_document_index =
    getDocumentManager().findDocument(current_document);

  return closeDocument(current_document_index);
}

bool ProjectWindow::saveDocument(
  api::document::IDocument
    *document)// NOLINT(readability-convert-member-functions-to-static)
{
  Q_ASSERT(document);

  getDocumentManager().switchToDocument(document);

  if (!document->getFileName().isEmpty())
    return getDocumentManager().saveDocument(document);
  else
    return getDocumentManager().saveDocumentAs(document);
}

bool ProjectWindow::saveDocumentAs(
  api::document::IDocument
    *document)// NOLINT(readability-convert-member-functions-to-static)
{
  Q_ASSERT(document);
  getDocumentManager().switchToDocument(document);
  return getDocumentManager().saveDocumentAs(document);
}

bool ProjectWindow::saveAllDocuments()
{
  for (const auto &document : getDocumentManager().getDocuments())
    if (!saveDocument(document.get())) return false;

  return true;
}

void ProjectWindow::
  performCut()// NOLINT(readability-convert-member-functions-to-static)
{
  if (auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(api::document::IDocumentEditor::CutAction);
}

void ProjectWindow::
  performCopy()// NOLINT(readability-convert-member-functions-to-static)
{
  if (auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(api::document::IDocumentEditor::CopyAction);
}

void ProjectWindow::
  performPaste()// NOLINT(readability-convert-member-functions-to-static)
{
  if (auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(api::document::IDocumentEditor::PasteAction);
}

void ProjectWindow::
  performDelete()// NOLINT(readability-convert-member-functions-to-static)
{
  if (auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(api::document::IDocumentEditor::DeleteAction);
}

void ProjectWindow::writeSettings()
{
  m_preferences->project_window_geometry = saveGeometry();
  m_preferences->project_window_state = saveState();

  getDocumentManager().saveState();
}

void ProjectWindow::readSettings()
{
  auto window_geometry = m_preferences->project_window_geometry.get();
  auto window_state = m_preferences->project_window_state.get();

  if (!window_geometry.isNull()) restoreGeometry(window_geometry);
  if (!window_state.isNull()) restoreState(window_state);

  getDocumentManager().restoreState();
}

void ProjectWindow::registerActions()
{
  getActionManager().registerAction(m_new_project_action, "new_project");
  getActionManager().registerAction(m_open_project_action, "open_project");
  getActionManager().registerAction(
    m_clear_recent_projects_action, "clear_recent_projects");
  getActionManager().registerAction(m_close_project_action, "close_project");
  getActionManager().registerAction(m_new_document_action, "new_document");
  getActionManager().registerAction(m_open_document_action, "open_document");
  getActionManager().registerAction(m_close_document_action, "close_document");
  getActionManager().registerAction(m_save_document_action, "save_document");
  getActionManager().registerAction(
    m_save_document_as_action, "save_document_as");
  getActionManager().registerAction(
    m_save_all_documents_action, "save_all_documents");
  getActionManager().registerAction(m_undo_action, "undo");
  getActionManager().registerAction(m_redo_action, "redo");
  getActionManager().registerAction(m_cut_action, "cut");
  getActionManager().registerAction(m_copy_action, "copy");
  getActionManager().registerAction(m_paste_action, "paste");
  getActionManager().registerAction(m_delete_action, "delete");
}

void ProjectWindow::initUi()
{
  m_ui->setupUi(this);

  setCentralWidget(getDocumentManager().getWidget());
  addDockWidget(Qt::LeftDockWidgetArea, m_project_dock);
  addDockWidget(Qt::BottomDockWidgetArea, m_console_dock);
  addDockWidget(Qt::BottomDockWidgetArea, m_issue_dock);
  tabifyDockWidget(m_console_dock, m_issue_dock);
  m_console_dock->raise();

  getDocumentManager().addEditor(
    api::document::IDocument::Type::Flow, std::make_unique<FlowEditor>());

  m_ui->m_menu_bar->addMenu(m_project_menu);
  m_project_menu->addAction(m_new_project_action);
  m_project_menu->addAction(m_open_project_action);
  m_project_menu->addMenu(m_open_recent_project_menu);
  m_open_recent_project_menu->addSeparator();
  m_open_recent_project_menu->addAction(m_clear_recent_projects_action);
  m_project_menu->addAction(m_close_project_action);
  m_project_menu->addSeparator();
  m_project_menu->addAction(getActionManager().findAction("settings"));
  m_project_menu->addSeparator();
  m_project_menu->addAction(getActionManager().findAction("exit"));

  m_ui->m_menu_bar->addMenu(m_document_menu);
  m_document_menu->addAction(m_new_document_action);
  m_document_menu->addAction(m_open_document_action);
  m_document_menu->addAction(m_close_document_action);
  m_document_menu->addSeparator();
  m_document_menu->addAction(m_save_document_action);
  m_document_menu->addAction(m_save_document_as_action);
  m_document_menu->addAction(m_save_all_documents_action);

  m_ui->m_menu_bar->addMenu(m_edit_menu);
  m_edit_menu->addAction(m_undo_action);
  m_edit_menu->addAction(m_redo_action);
  m_edit_menu->addSeparator();
  m_edit_menu->addAction(m_cut_action);
  m_edit_menu->addAction(m_copy_action);
  m_edit_menu->addAction(m_paste_action);
  m_edit_menu->addAction(m_delete_action);

  m_ui->m_menu_bar->addMenu(m_view_menu);
  m_view_menu->addMenu(m_views_and_toolbars_menu);

  m_ui->m_menu_bar->addMenu(m_help_menu);
  m_help_menu->addAction(getActionManager().findAction("about"));

  m_help_menu->setShortcutEnabled(true);
}

void ProjectWindow::initConnections()
{
  auto undoGroup = getDocumentManager().getUndoGroup();

  connect(
    getDocumentManager().getEditor(api::document::IDocument::Type::Flow),
    &api::document::IDocumentEditor::enabledStandardActionsChanged, this,
    &ProjectWindow::updateActions);

  connect(
    undoGroup, &QUndoGroup::cleanChanged, this,
    &ProjectWindow::updateWindowTitle);

  connect(
    m_new_project_action, &QAction::triggered, this,
    &ProjectWindow::newProject);
  connect(
    m_open_project_action, &QAction::triggered, this,
    qOverload<>(&ProjectWindow::openProject));
  connect(m_clear_recent_projects_action, &QAction::triggered, this, []() {
    getPreferencesManager().clearRecentProjectFiles();
  });
  connect(
    m_close_project_action, &QAction::triggered, this,
    &ProjectWindow::closeProject);

  connect(
    m_new_document_action, &QAction::triggered, this,
    &ProjectWindow::newDocument);
  connect(
    m_open_document_action, &QAction::triggered, this,
    qOverload<>(&ProjectWindow::openDocument));
  connect(
    m_close_document_action, &QAction::triggered, this,
    qOverload<>(&ProjectWindow::closeDocument));
  connect(m_save_document_action, &QAction::triggered, this, [this]() {
    saveDocument(getDocumentManager().getCurrentDocument());
  });
  connect(m_save_document_as_action, &QAction::triggered, this, [this]() {
    saveDocumentAs(getDocumentManager().getCurrentDocument());
  });
  connect(
    m_save_all_documents_action, &QAction::triggered, this,
    &ProjectWindow::saveAllDocuments);

  connect(m_cut_action, &QAction::triggered, this, &ProjectWindow::performCut);
  connect(
    m_copy_action, &QAction::triggered, this, &ProjectWindow::performCopy);
  connect(
    m_paste_action, &QAction::triggered, this, &ProjectWindow::performPaste);
  connect(
    m_delete_action, &QAction::triggered, this, &ProjectWindow::performDelete);

  connect(
    m_views_and_toolbars_menu, &QMenu::aboutToShow, this,
    &ProjectWindow::updateViewsAndToolbarsMenu);

  connect(
    &getDocumentManager(), &DocumentManager::currentDocumentChanged, this,
    &ProjectWindow::documentChanged);
  connect(
    &getDocumentManager(), &DocumentManager::documentCloseRequested, this,
    qOverload<>(&ProjectWindow::closeDocument));

  connect(
    &getProjectManager(), &ProjectManager::currentProjectChanged, this,
    &ProjectWindow::projectChanged);

  connect(
    &getPreferencesManager(), &PreferencesManager::recentProjectFilesChanged,
    this, &ProjectWindow::updateRecentProjectFiles);
}

void ProjectWindow::retranslateUi()
{
  m_ui->retranslateUi(this);

  m_project_menu->setTitle(tr("&Project"));
  m_new_project_action->setText(tr("&New..."));
  m_new_project_action->setWhatsThis(tr("New Project"));
  m_open_project_action->setText(tr("&Open..."));
  m_open_project_action->setWhatsThis(tr("Open Project"));
  m_open_recent_project_menu->setTitle(tr("Open &Recent"));
  m_clear_recent_projects_action->setText(tr("Clear &Recent"));
  m_clear_recent_projects_action->setWhatsThis(tr("Clear Recent Project"));
  m_close_project_action->setText(tr("&Close Project"));
  m_close_project_action->setWhatsThis(tr("Close Project"));

  m_document_menu->setTitle(tr("&Document"));
  m_new_document_action->setText(tr("&New..."));
  m_new_document_action->setWhatsThis(tr("New Document"));
  m_open_document_action->setText(tr("&Open..."));
  m_open_document_action->setWhatsThis(tr("Open Document"));
  m_close_document_action->setText(tr("&Close Document"));
  m_close_document_action->setWhatsThis(tr("Close Document"));
  m_save_document_action->setText(tr("&Save"));
  m_save_document_action->setWhatsThis(tr("Save Document"));
  m_save_document_as_action->setText(tr("Save &As"));
  m_save_document_as_action->setWhatsThis(tr("Save Document As"));
  m_save_all_documents_action->setText(tr("Save All"));
  m_save_all_documents_action->setWhatsThis(tr("Save All Documents"));

  m_edit_menu->setTitle(tr("&Edit"));
  m_undo_action->setText(tr("&Undo"));
  m_undo_action->setWhatsThis(tr("Undo"));
  m_redo_action->setText(tr("&Redo"));
  m_redo_action->setWhatsThis(tr("Redo"));
  m_cut_action->setText(tr("&Cut"));
  m_cut_action->setWhatsThis(tr("Cut"));
  m_copy_action->setText(tr("&Copy"));
  m_copy_action->setWhatsThis(tr("Copy"));
  m_paste_action->setText(tr("&Paste"));
  m_paste_action->setWhatsThis(tr("Paste"));
  m_delete_action->setText(tr("&Delete"));
  m_delete_action->setWhatsThis(tr("Delete"));

  m_view_menu->setTitle(tr("&View"));
  m_views_and_toolbars_menu->setTitle(tr("Views and &Toolbars"));

  m_help_menu->setTitle(tr("&Help"));

  adjustMenuSize(this);
}

bool ProjectWindow::switchProject(
  std::unique_ptr<api::project::IProject> project)
{
  auto ret = QMessageBox::warning(
    this, tr("Open Project"),
    tr("There is currently open project. Do you "
       "want to close it and open new one now?"),
    QMessageBox::Yes | QMessageBox::Cancel);

  if (ret == QMessageBox::Yes && closeProject())
  {
    auto project_ptr = project.get();

    getProjectManager().removeAllProjects();
    getProjectManager().addProject(std::move(project));
    getPreferencesManager().addRecentProjectFile(project_ptr->getFileName());
    return true;
  }

  return false;
}
