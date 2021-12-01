/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/main_window.h"
#include "flow/tools/editor/preferences_manager.h"
#include "flow/tools/editor/language_manager.h"
#include "flow/tools/editor/action_manager.h"
#include "flow/tools/editor/style_manager.h"
#include "flow/tools/editor/about_dialog.h"
#include "flow/tools/editor/document/document_manager.h"
#include "flow/tools/editor/document/flow_editor.h"
#include "flow/tools/editor/document/document.h"
#include "flow/tools/editor/document/new_document_dialog.h"
/* -------------------------------- Tools Shared ---------------------------- */
#include <flow/tools/shared/qtdialog/qtdialogwithtoggleview.h>
#include <flow/tools/shared/qtdialog/qtextendedfiledialog.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_main_window.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct MainWindow::Preferences
{
  Preference<QByteArray> main_window_geometry = Preference<QByteArray>("main_window/geometry");
  Preference<QByteArray> main_window_state = Preference<QByteArray>("main_window/state");
  Preference<QLocale> application_language = Preference<QLocale>("application/language");
  Preference<QString> application_style = Preference<QString>("application/style");
};

/* -------------------------------- MainWindow ------------------------------ */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow()),
    m_preferences(new Preferences)
{
  m_ui->setupUi(this);

  registerMenus();
  registerActions();
  registerConnections();

  setCentralWidget(getDocumentManager().getWidget());

  getDocumentManager().addEditor(Document::Type::Flow, std::make_unique<FlowEditor>());
  connect(getDocumentManager().getEditor(Document::Type::Flow),
          &DocumentEditor::enabledStandardActionsChanged, this, &MainWindow::updateActions);

  updateActions();
  updateWindowTitle();
  updateRecentDocumentFiles();

  readSettings();
  retranslateUi();
}

MainWindow::~MainWindow()
{
  DocumentManager::deleteInstance();
  LanguageManager::deleteInstance();
  ActionManager::deleteInstance();
  StyleManager::deleteInstance();
  PreferencesManager::deleteInstance();
}

DocumentManager& MainWindow::getDocumentManager() const // NOLINT(readability-convert-member-functions-to-static)
{
  return DocumentManager::getInstance();
}

LanguageManager& MainWindow::getLanguageManager() const // NOLINT(readability-convert-member-functions-to-static)
{
  return LanguageManager::getInstance();
}

StyleManager& MainWindow::getStyleManager() const // NOLINT(readability-convert-member-functions-to-static)
{
  return StyleManager::getInstance();
}

ActionManager& MainWindow::getActionManager() const // NOLINT(readability-convert-member-functions-to-static)
{
  return ActionManager::getInstance();
}

PreferencesManager& MainWindow::getPreferencesManager() const // NOLINT(readability-convert-member-functions-to-static)
{
  return PreferencesManager::getInstance();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (confirmAllSave() && closeDocument())
  {
    writeSettings();
    event->accept();
  }
  else
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

void MainWindow::documentChanged(Document* document)
{
  updateWindowTitle();
  updateActions();
}

bool MainWindow::confirmSave(Document* document)
{
  if(!document || !document->isModified())
    return true;

  getDocumentManager().switchToDocument(document);

  auto ret = QMessageBox::warning(
      this, tr("Unsaved Changes"),
      tr("There are unsaved changes. Do you want to save now?"),
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (ret) {
    case QMessageBox::Save:    return saveDocument(document);
    case QMessageBox::Discard: return true;
    case QMessageBox::Cancel:
    default:
      return false;
  }
}

bool MainWindow::confirmAllSave()
{
  for(const auto& project : getDocumentManager().getDocuments()) // NOLINT(readability-use-anyofallof)
    if(!confirmSave(project.get())) return false;

  return true;
}

void MainWindow::updateActions() // NOLINT(readability-make-member-function-const)
{
  auto document_editor = getDocumentManager().getCurrentEditor();
  auto current_document = getDocumentManager().getCurrentDocument();

  DocumentEditor::StandardActions standard_actions;
  if(document_editor)
    standard_actions = document_editor->getEnabledStandardActions();

  getActionManager().findAction("close_document")->setEnabled(current_document);
  getActionManager().findAction("close_document")->setEnabled(current_document);
  getActionManager().findAction("save_document")->setEnabled(current_document);
  getActionManager().findAction("save_document_as")->setEnabled(current_document);
  getActionManager().findAction("save_all_documents")->setEnabled(current_document);

  getActionManager().findAction("cut")->setEnabled(standard_actions & DocumentEditor::CutAction);
  getActionManager().findAction("copy")->setEnabled(standard_actions & DocumentEditor::CopyAction);
  getActionManager().findAction("paste")->setEnabled(standard_actions & DocumentEditor::PasteAction);
  getActionManager().findAction("delete")->setEnabled(standard_actions & DocumentEditor::DeleteAction);

  getActionManager().findMenu("views_and_toolbars")->setEnabled(current_document);
}

void MainWindow::updateWindowTitle()
{
  auto current_document = getDocumentManager().getCurrentDocument();

  auto project_name = current_document ? QString("[*]%1").arg(current_document->getDisplayName()) : QString();
  auto project_file_path = current_document ? current_document->getFileName() : QString();

  setWindowTitle(project_name);
  setWindowFilePath(project_file_path);
}

void MainWindow::updateViewsAndToolbarsMenu() // NOLINT(readability-make-member-function-const)
{
  auto view_and_toolbars_menu = getActionManager().findMenu("views_and_toolbars");
  view_and_toolbars_menu->clear();

  if(auto editor = getDocumentManager().getCurrentEditor())
  {
    auto dockWidgets = editor->getDockWidgets();
    auto dialogWidgets = editor->getDialogWidgets();

    for(auto& dockWidget : dockWidgets)
      view_and_toolbars_menu->addAction(dockWidget->toggleViewAction());

    view_and_toolbars_menu->addSeparator();

    for(auto& dialogWidget : dialogWidgets)
      view_and_toolbars_menu->addAction(dialogWidget->toggleViewAction());
  }
}

void MainWindow::updateRecentDocumentFiles() // NOLINT(readability-make-member-function-const)
{
  auto recent_document_files = getPreferencesManager().getRecentDocumentFiles();
  auto open_recent_document_menu = getActionManager().findMenu("open_recent_document");
  auto clear_recent_documents_action = getActionManager().findAction("clear_recent_documents");

  for(auto& action : open_recent_document_menu->actions())
  {
    if(action != clear_recent_documents_action)
      action->deleteLater();
  }

  for(auto& recent_project_file : recent_document_files)
  {
    auto fileInfo = QFileInfo(recent_project_file);
    if(!fileInfo.exists())
      continue;

    auto open_recent_document_action = new QAction(open_recent_document_menu);
    open_recent_document_action->setText(fileInfo.fileName());
    open_recent_document_action->setToolTip(fileInfo.filePath());
    open_recent_document_action->setVisible(true);

    open_recent_document_menu->insertAction(clear_recent_documents_action, open_recent_document_action);

    connect(open_recent_document_action, &QAction::triggered, this, [this, recent_project_file](){
      getDocumentManager().loadDocument(recent_project_file);
    });
  }

  open_recent_document_menu->insertSeparator(clear_recent_documents_action);
}

void MainWindow::clearRecent() // NOLINT(readability-make-member-function-const)
{
  getPreferencesManager().clearRecentDocumentFiles();
}

void MainWindow::openSettings()
{
  // TODO Implementation
}

void MainWindow::newDocument()
{
  auto new_document_dialog = QScopedPointer<NewDocumentDialog>(new NewDocumentDialog(this));
  if(auto document = new_document_dialog->create(); document)
    getDocumentManager().addDocument(std::move(document));
}

void MainWindow::openDocument()
{
  // TODO Implementation
}

bool MainWindow::closeDocument(int index) // NOLINT(readability-make-member-function-const)
{
  auto document = getDocumentManager().getDocument(index);
  if(document)
  {
    if(!confirmSave(document))
      return false;

    getDocumentManager().removeDocument(index);
  }

  return true;
}

bool MainWindow::closeDocument() // NOLINT(readability-convert-member-functions-to-static)
{
  auto current_document = getDocumentManager().getCurrentDocument();
  auto current_document_index = getDocumentManager().findDocument(current_document);

  return closeDocument(current_document_index);
}

bool MainWindow::saveDocument(Document* document) // NOLINT(readability-make-member-function-const)
{
  Q_ASSERT(document);
  getDocumentManager().switchToDocument(document);
  return getDocumentManager().saveDocument(document);
}

bool MainWindow::saveDocumentAs(Document* document) // NOLINT(readability-make-member-function-const)
{
  Q_ASSERT(document);
  getDocumentManager().switchToDocument(document);
  return getDocumentManager().saveDocumentAs(document);
}

bool MainWindow::saveAllDocuments()
{
  for(const auto& document : getDocumentManager().getDocuments()) // NOLINT(readability-use-anyofallof)
    if(!saveDocument(document.get())) return false;

  return true;
}

void MainWindow::performCut() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::CutAction);
}

void MainWindow::performCopy() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::CopyAction);
}

void MainWindow::performPaste() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::PasteAction);
}

void MainWindow::performDelete() // NOLINT(readability-make-member-function-const)
{
  if(auto editor = getDocumentManager().getCurrentEditor())
    editor->performStandardAction(DocumentEditor::DeleteAction);
}

void MainWindow::openAbout()
{
  if(!m_about_dialog)
  {
    m_about_dialog = new AboutDialog(this);
    m_about_dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  m_about_dialog->show();
  m_about_dialog->activateWindow();
  m_about_dialog->raise();
}

void MainWindow::writeSettings()
{
  m_preferences->main_window_geometry = saveGeometry();
  m_preferences->main_window_state = saveState();

  m_preferences->application_language = getLanguageManager().getCurrentLanguage();
  m_preferences->application_style = getStyleManager().getCurrentStyle();

  getDocumentManager().saveState();
}

void MainWindow::readSettings()
{
  auto main_window_geometry = m_preferences->main_window_geometry.get();
  auto main_window_state = m_preferences->main_window_state.get();

  auto application_language = m_preferences->application_language.get();
  auto application_style = m_preferences->application_style.get();

  if(!main_window_geometry.isNull()) restoreGeometry(main_window_geometry);
  if(!main_window_state.isNull()) restoreState(main_window_state);

  auto languages = getLanguageManager().getAvailableLanguages();
  if(languages.contains(application_language))
    getLanguageManager().setLanguage(application_language);
  else if(languages.contains(QLocale::system()))
    getLanguageManager().setLanguage(QLocale::system());

  if(!application_style.isEmpty())
    getStyleManager().setStyle(application_style);

  getDocumentManager().restoreState();
}

void MainWindow::registerMenus()
{
  getActionManager().registerMenu(m_ui->m_menu_file, "file");
  getActionManager().registerMenu(m_ui->m_menu_open_recent_document, "open_recent_document");

  getActionManager().registerMenu(m_ui->m_menu_edit, "edit");

  getActionManager().registerMenu(m_ui->m_menu_view, "view");
  getActionManager().registerMenu(m_ui->m_menu_views_and_toolbars, "views_and_toolbars");

  getActionManager().registerMenu(m_ui->m_menu_help, "help");
}

void MainWindow::registerActions()
{
  getActionManager().registerAction(m_ui->m_action_new_document, "new_document");
  getActionManager().registerAction(m_ui->m_action_open_document, "open_document");
  getActionManager().registerAction(m_ui->m_action_clear_recent_documents, "clear_recent_documents");
  getActionManager().registerAction(m_ui->m_action_close_document, "close_document");
  getActionManager().registerAction(m_ui->m_action_save, "save_document");
  getActionManager().registerAction(m_ui->m_action_save_as, "save_document_as");
  getActionManager().registerAction(m_ui->m_action_save_all, "save_all_documents");
  getActionManager().registerAction(m_ui->m_action_settings, "settings");
  getActionManager().registerAction(m_ui->m_action_exit, "exit");

  getActionManager().registerAction(m_ui->m_action_cut, "cut");
  getActionManager().registerAction(m_ui->m_action_copy, "copy");
  getActionManager().registerAction(m_ui->m_action_paste, "paste");
  getActionManager().registerAction(m_ui->m_action_delete, "delete");

  getActionManager().registerAction(m_ui->m_action_about, "about");
}

void MainWindow::registerConnections()
{
  auto undoGroup = getDocumentManager().getUndoGroup();
  auto undoAction = undoGroup->createUndoAction(this, tr("&Undo"));
  auto redoAction = undoGroup->createRedoAction(this, tr("&Redo"));

  m_ui->m_menu_edit->insertAction(m_ui->m_action_cut, undoAction);
  m_ui->m_menu_edit->insertAction(m_ui->m_action_cut, redoAction);
  m_ui->m_menu_edit->insertSeparator(m_ui->m_action_cut);

  getActionManager().registerAction(undoAction, "undo");
  getActionManager().registerAction(redoAction, "redo");

  connect(undoGroup, &QUndoGroup::cleanChanged, this, &MainWindow::updateWindowTitle);

  connect(getActionManager().findAction("new_document"), &QAction::triggered, this, &MainWindow::newDocument);
  connect(getActionManager().findAction("open_document"), &QAction::triggered, this, qOverload<>(&MainWindow::openDocument));
  connect(getActionManager().findAction("clear_recent_documents"), &QAction::triggered, this, &MainWindow::clearRecent);
  connect(getActionManager().findAction("close_document"), &QAction::triggered, this, qOverload<>(&MainWindow::closeDocument));
  connect(getActionManager().findAction("save_document"), &QAction::triggered, this, [this](){
    saveDocument(getDocumentManager().getCurrentDocument());
  });
  connect(getActionManager().findAction("save_document_as"), &QAction::triggered, this, [this](){
    saveDocumentAs(getDocumentManager().getCurrentDocument());
  });
  connect(getActionManager().findAction("save_all_documents"), &QAction::triggered, this, &MainWindow::saveAllDocuments);

  connect(getActionManager().findAction("settings"), &QAction::triggered, this, &MainWindow::openSettings);
  connect(getActionManager().findAction("exit"), &QAction::triggered, this, &MainWindow::close);

  connect(getActionManager().findAction("cut"), &QAction::triggered, this, &MainWindow::performCut);
  connect(getActionManager().findAction("copy"), &QAction::triggered, this, &MainWindow::performCopy);
  connect(getActionManager().findAction("paste"), &QAction::triggered, this, &MainWindow::performPaste);
  connect(getActionManager().findAction("delete"), &QAction::triggered, this, &MainWindow::performDelete);

  connect(getActionManager().findAction("about"), &QAction::triggered, this, &MainWindow::openAbout);

  connect(getActionManager().findMenu("views_and_toolbars"), &QMenu::aboutToShow, this, &MainWindow::updateViewsAndToolbarsMenu);

  connect(&getDocumentManager(), &DocumentManager::currentDocumentChanged, this, &MainWindow::documentChanged);
  connect(&getDocumentManager(), &DocumentManager::documentCloseRequested, this, qOverload<>(&MainWindow::closeDocument));

  connect(&getPreferencesManager(), &PreferencesManager::recentDocumentFilesChanged, this, &MainWindow::updateRecentDocumentFiles);
}

void MainWindow::retranslateUi() // NOLINT(readability-make-member-function-const)
{
  m_ui->retranslateUi(this);

  updateWindowTitle();

  getActionManager().findMenu("file")->setTitle(tr("&File"));
  getActionManager().findMenu("open_recent_document")->setTitle(tr("Open &Recent"));
  getActionManager().findAction("new_document")->setText(tr("&New..."));
  getActionManager().findAction("open_document")->setText(tr("&Open..."));
  getActionManager().findAction("clear_recent_documents")->setText(tr("Clear &Recent"));
  getActionManager().findAction("close_document")->setText(tr("&Close Document"));
  getActionManager().findAction("save_document")->setText(tr("&Save"));
  getActionManager().findAction("save_document_as")->setText(tr("Save &As"));
  getActionManager().findAction("save_all_documents")->setText(tr("Save All"));
  getActionManager().findAction("settings")->setText(tr("&Settings..."));
  getActionManager().findAction("exit")->setText(tr("&Exit"));

  getActionManager().findMenu("edit")->setTitle(tr("&Edit"));
  getActionManager().findAction("undo")->setText(tr("&Undo"));
  getActionManager().findAction("redo")->setText(tr("&Redo"));
  getActionManager().findAction("cut")->setText(tr("&Cut"));
  getActionManager().findAction("copy")->setText(tr("&Copy"));
  getActionManager().findAction("paste")->setText(tr("&Paste"));
  getActionManager().findAction("delete")->setText(tr("&Delete"));

  getActionManager().findMenu("view")->setTitle(tr("&View"));
  getActionManager().findMenu("views_and_toolbars")->setTitle(tr("Views and &Toolbars"));

  getActionManager().findMenu("help")->setTitle(tr("&Help"));
  getActionManager().findAction("about")->setText(tr("&About..."));
}
