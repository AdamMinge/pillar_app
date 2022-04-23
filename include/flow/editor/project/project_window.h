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

namespace flow
{
  namespace project
  {
    class Project;
  }
  namespace document
  {
    class Document;
  }
}// namespace api

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

private Q_SLOTS:
  void documentChanged(flow::document::Document *document);
  void projectChanged(flow::project::Project *project);

  bool confirmSave(flow::document::Document *document);
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
  bool saveDocument(flow::document::Document *document);
  bool saveDocumentAs(flow::document::Document *document);
  bool saveAllDocuments();

  void performCut();
  void performCopy();
  void performPaste();
  void performDelete();

private:
  void registerActions();

  void initUi();
  void initConnections();

  void retranslateUi();

  bool switchProject(std::unique_ptr<flow::project::Project> project);

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
