#ifndef FLOW_DOCUMENT_MANAGER_H
#define FLOW_DOCUMENT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QObject>
#include <QPointer>
#include <QScopedPointer>
#include <QStackedLayout>
#include <QTabBar>
#include <QUndoGroup>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <unordered_map>
#include <vector>
/* ------------------------------------ Api --------------------------------- */
#include "flow/api/document.h"
/* -------------------------------------------------------------------------- */

class NoDocumentWidget;
class DocumentEditor;
namespace utils
{
  class QtFileSystemWatcher;
}

class DocumentManager : public QObject
{
  Q_OBJECT

public:
  static DocumentManager &getInstance();
  static void deleteInstance();

public:
  ~DocumentManager() override;

  [[nodiscard]] QWidget *getWidget() const;

  void addEditor(api::IDocument::Type document_type, std::unique_ptr<DocumentEditor> editor);
  void removeEditor(api::IDocument::Type document_type);
  void removeAllEditors();

  [[nodiscard]] DocumentEditor *getEditor(api::IDocument::Type document_type) const;
  [[nodiscard]] DocumentEditor *getCurrentEditor() const;

  void addDocument(std::unique_ptr<api::IDocument> document);
  void insertDocument(int index, std::unique_ptr<api::IDocument> document);

  void removeDocument(int index);
  void removeAllDocuments();

  [[nodiscard]] api::IDocument *getDocument(int index) const;
  [[nodiscard]] api::IDocument *getCurrentDocument() const;

  [[nodiscard]] int findDocument(api::IDocument *document) const;
  [[nodiscard]] int findDocument(const QString &file_name) const;

  void switchToDocument(int index);
  void switchToDocument(api::IDocument *document);
  bool switchToDocument(const QString &file_name);

  [[nodiscard]] QUndoGroup *getUndoGroup() const;

  void saveState();
  void restoreState();

  bool saveDocument(api::IDocument *document);
  bool saveDocumentAs(api::IDocument *document);

  bool reloadDocumentAt(int index);
  bool loadDocument(const QString &file_name);

  [[nodiscard]] const std::vector<std::unique_ptr<api::IDocument>> &getDocuments() const;

Q_SIGNALS:
  void currentDocumentChanged(api::IDocument *document);
  void documentCloseRequested(int index);

protected:
  explicit DocumentManager();

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);

  void filesChanged(const QStringList &file_names);
  void fileNameChanged(const QString &new_file_name, const QString &old_file_name);
  void updateDocumentTab(api::IDocument *document);

private:
  static QScopedPointer<DocumentManager> m_instance;

  std::vector<std::unique_ptr<api::IDocument>> m_documents;
  std::unordered_map<api::IDocument::Type, std::unique_ptr<DocumentEditor>> m_editor_for_document_type;

  QPointer<QWidget> m_widget;
  NoDocumentWidget *m_no_document_widget;
  QTabBar *m_tab_bar;
  QStackedLayout *m_editor_stack;

  QScopedPointer<utils::QtFileSystemWatcher> m_file_system_watcher;
  QUndoGroup *m_undo_group;
};

#endif//FLOW_DOCUMENT_MANAGER_H
