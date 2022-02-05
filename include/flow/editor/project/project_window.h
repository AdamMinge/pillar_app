#ifndef FLOW_PROJECT_WINDOW_H
#define FLOW_PROJECT_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
#include <memory>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class ProjectWindow;
}

namespace api
{
  namespace project
  {
    class IProject;
  }
  namespace document
  {
    class IDocument;
  }
}// namespace api

class PreferencesManager;
class DocumentManager;
class ProjectManager;
class ActionManager;

class ProjectDock;
class ConsoleDock;
class IssueDock;

class ProjectWindow : public QMainWindow
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit ProjectWindow(QWidget *parent = nullptr);
  ~ProjectWindow() override;

  void writeSettings();
  void readSettings();

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

  [[nodiscard]] static DocumentManager &getDocumentManager();
  [[nodiscard]] static ProjectManager &getProjectManager();
  [[nodiscard]] static ActionManager &getActionManager();
  [[nodiscard]] static PreferencesManager &getPreferencesManager();

private Q_SLOTS:
  void documentChanged(api::document::IDocument *document);
  void projectChanged(api::project::IProject *project);

  bool confirmSave(api::document::IDocument *document);
  bool confirmAllSave();

  void updateActions();
  void updateWindowTitle();
  void updateViewsAndToolbarsMenu();
  void updateRecentProjectFiles();

  void newProject();
  void openProject();
  bool openProject(const QString &file_name);
  bool closeProject();

  void newDocument();
  void openDocument();
  bool closeDocument(int index);
  bool closeDocument();
  bool saveDocument(api::document::IDocument *document);
  bool saveDocumentAs(api::document::IDocument *document);
  bool saveAllDocuments();

  void performCut();
  void performCopy();
  void performPaste();
  void performDelete();

private:
  void initUi();
  void initConnections();

  void retranslateUi();

  bool switchProject(std::unique_ptr<api::project::IProject> project);

private:
  QScopedPointer<Ui::ProjectWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;

  ProjectDock *m_project_dock;
  ConsoleDock *m_console_dock;
  IssueDock *m_issue_dock;

  QMenu *m_project_menu;
  QAction *m_new_project_action;
  QAction *m_open_project_action;
  QMenu *m_open_recent_project_menu;
  QAction *m_clear_recent_projects_action;
  QAction *m_close_project_action;

  QMenu *m_document_menu;
  QAction *m_new_document_action;
  QAction *m_open_document_action;
  QAction *m_close_document_action;
  QAction *m_save_document_action;
  QAction *m_save_document_as_action;
  QAction *m_save_all_documents_action;

  QMenu *m_edit_menu;
  QAction *m_undo_action;
  QAction *m_redo_action;
  QAction *m_cut_action;
  QAction *m_copy_action;
  QAction *m_paste_action;
  QAction *m_delete_action;

  QMenu *m_view_menu;
  QMenu *m_views_and_toolbars_menu;

  QMenu *m_help_menu;
};

#endif//FLOW_PROJECT_WINDOW_H
