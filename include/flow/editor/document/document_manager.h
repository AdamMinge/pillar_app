#ifndef FLOW_DOCUMENT_MANAGER_H
#define FLOW_DOCUMENT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QPointer>
#include <QScopedPointer>
#include <QStackedLayout>
#include <QTabBar>
/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/api/document/document_manager.h>
/* -------------------------------------------------------------------------- */

class NoDocumentWidget;

namespace utils
{
  class QtFileSystemWatcher;
}

class DocumentManager : public api::document::IDocumentManager
{
  Q_OBJECT

public:
  static DocumentManager &getInstance();
  static void deleteInstance();

public:
  ~DocumentManager() override;

  [[nodiscard]] QWidget *getWidget() const override;

  void
  addEditor(api::document::IDocument::Type document_type,
            std::unique_ptr<api::document::IDocumentEditor> editor) override;
  void removeEditor(api::document::IDocument::Type document_type) override;
  void removeAllEditors() override;

  [[nodiscard]] api::document::IDocumentEditor *
  getEditor(api::document::IDocument::Type document_type) const override;
  [[nodiscard]] api::document::IDocumentEditor *
  getCurrentEditor() const override;

  void addDocument(std::unique_ptr<api::document::IDocument> document) override;
  void
  insertDocument(int index,
                 std::unique_ptr<api::document::IDocument> document) override;

  void removeDocument(int index) override;
  void removeAllDocuments() override;

  [[nodiscard]] api::document::IDocument *getDocument(int index) const override;
  [[nodiscard]] api::document::IDocument *getCurrentDocument() const override;

  [[nodiscard]] int
  findDocument(api::document::IDocument *document) const override;
  [[nodiscard]] int findDocument(const QString &file_name) const override;

  void switchToDocument(int index) override;
  void switchToDocument(api::document::IDocument *document) override;
  bool switchToDocument(const QString &file_name) override;

  [[nodiscard]] QUndoGroup *getUndoGroup() const override;

  void saveState() override;
  void restoreState() override;

  bool saveDocument(api::document::IDocument *document) override;
  bool saveDocumentAs(api::document::IDocument *document) override;

  bool reloadDocumentAt(int index) override;
  bool loadDocument(const QString &file_name) override;

  [[nodiscard]] const std::vector<std::unique_ptr<api::document::IDocument>> &
  getDocuments() const override;

protected:
  explicit DocumentManager();

private Q_SLOTS:
  void currentIndexChanged();
  void documentTabMoved(int from, int to);

  void filesChanged(const QStringList &file_names);
  void fileNameChanged(const QString &new_file_name,
                       const QString &old_file_name);
  void updateDocumentTab(api::document::IDocument *document);

private:
  static QScopedPointer<DocumentManager> m_instance;

  std::vector<std::unique_ptr<api::document::IDocument>> m_documents;
  std::unordered_map<api::document::IDocument::Type,
                     std::unique_ptr<api::document::IDocumentEditor>>
    m_editor_for_document_type;

  QPointer<QWidget> m_widget;
  NoDocumentWidget *m_no_document_widget;
  QTabBar *m_tab_bar;
  QStackedLayout *m_editor_stack;

  QScopedPointer<utils::QtFileSystemWatcher> m_file_system_watcher;
  QUndoGroup *m_undo_group;
};

#endif//FLOW_DOCUMENT_MANAGER_H
