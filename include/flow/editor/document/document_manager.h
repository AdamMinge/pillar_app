#ifndef FLOW_DOCUMENT_MANAGER_H
#define FLOW_DOCUMENT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QPointer>
#include <QScopedPointer>
#include <QStackedLayout>
#include <QTabBar>
#include <QUndoGroup>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
/* --------------------------------- LibFlow -------------------------------- */
#include <flow/libflow/plugin_listener.h>
/* -------------------------------------------------------------------------- */

class NoDocumentWidget;

namespace utils
{
  class QtFileSystemWatcher;
}

namespace flow::document
{
  class Document;
  class DocumentEditor;
}// namespace flow::document

class DocumentManager
    : public QObject,
      public flow::PluginListener<flow::document::DocumentEditor>
{
  Q_OBJECT

public:
  static DocumentManager &getInstance();
  static void deleteInstance();

public:
  ~DocumentManager() override;

  [[nodiscard]] QWidget *getWidget() const;

  void addEditor(flow::document::DocumentEditor *editor);
  void removeEditor(const QString &document_id);
  void removeAllEditors();

  [[nodiscard]] flow::document::DocumentEditor *
  getEditor(const QString &document_id) const;
  [[nodiscard]] flow::document::DocumentEditor *getCurrentEditor() const;

  void addDocument(std::unique_ptr<flow::document::Document> document);
  void
  insertDocument(int index, std::unique_ptr<flow::document::Document> document);

  void removeDocument(int index);
  void removeAllDocuments();

  [[nodiscard]] flow::document::Document *getDocument(int index) const;
  [[nodiscard]] flow::document::Document *getCurrentDocument() const;

  [[nodiscard]] int findDocument(flow::document::Document *document) const;
  [[nodiscard]] int findDocument(const QString &file_name) const;

  void switchToDocument(int index);
  void switchToDocument(flow::document::Document *document);
  bool switchToDocument(const QString &file_name);

  [[nodiscard]] QUndoGroup *getUndoGroup() const;

  void saveState();
  void restoreState();

  bool saveDocument(flow::document::Document *document);
  bool saveDocumentAs(flow::document::Document *document);

  bool reloadDocumentAt(int index);
  bool loadDocument(const QString &file_name);

  [[nodiscard]] const std::vector<std::unique_ptr<flow::document::Document>> &
  getDocuments() const;

protected:
  explicit DocumentManager();

  void addedObject(flow::document::DocumentEditor *object) override;
  void removedObject(flow::document::DocumentEditor *object) override;

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);

  void filesChanged(const QStringList &file_names);
  void
  fileNameChanged(const QString &new_file_name, const QString &old_file_name);
  void updateDocumentTab(flow::document::Document *document);

Q_SIGNALS:
  void currentDocumentChanged(flow::document::Document *document);
  void documentCloseRequested(int index);
  void enabledStandardActionsChanged();

private:
  static QScopedPointer<DocumentManager> m_instance;

  std::vector<std::unique_ptr<flow::document::Document>> m_documents;
  std::unordered_map<QString, flow::document::DocumentEditor *>
    m_editor_for_document_id;

  QPointer<QWidget> m_widget;
  NoDocumentWidget *m_no_document_widget;
  QTabBar *m_tab_bar;
  QStackedLayout *m_editor_stack;

  QScopedPointer<utils::QtFileSystemWatcher> m_file_system_watcher;
  QUndoGroup *m_undo_group;
};

#endif//FLOW_DOCUMENT_MANAGER_H
