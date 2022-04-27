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
/* ---------------------------------- Local --------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/plugin_listener.h"
/* -------------------------------------------------------------------------- */

namespace utils
{
  class QtFileSystemWatcher;
}

namespace flow::document
{

  class Document;
  class DocumentEditor;

  class LIB_FLOW_API DocumentManager : public QObject,
                                       public PluginListener<DocumentEditor>
  {
    Q_OBJECT

  public:
    static DocumentManager &getInstance();
    static void deleteInstance();

  public:
    ~DocumentManager() override;

    [[nodiscard]] QWidget *getWidget() const;

    void addEditor(DocumentEditor *editor);
    void removeEditor(const QString &document_id);
    void removeAllEditors();

    [[nodiscard]] DocumentEditor *getEditor(const QString &document_id) const;
    [[nodiscard]] DocumentEditor *getCurrentEditor() const;

    void addDocument(std::unique_ptr<Document> document);
    void insertDocument(int index, std::unique_ptr<Document> document);

    void removeDocument(int index);
    void removeAllDocuments();

    [[nodiscard]] Document *getDocument(int index) const;
    [[nodiscard]] Document *getCurrentDocument() const;

    [[nodiscard]] int findDocument(Document *document) const;
    [[nodiscard]] int findDocument(const QString &file_name) const;

    void switchToDocument(int index);
    void switchToDocument(Document *document);
    bool switchToDocument(const QString &file_name);

    [[nodiscard]] QUndoGroup *getUndoGroup() const;

    void saveState();
    void restoreState();

    bool saveDocument(Document *document);
    bool saveDocumentAs(Document *document);

    bool reloadDocumentAt(int index);
    bool loadDocument(const QString &file_name);

    [[nodiscard]] const std::vector<std::unique_ptr<Document>> &
    getDocuments() const;

  protected:
    explicit DocumentManager();

    void addedObject(DocumentEditor *object) override;
    void removedObject(DocumentEditor *object) override;

  private Q_SLOTS:
    void currentIndexChanged();
    void documentTabMoved(int from, int to);

    void filesChanged(const QStringList &file_names);
    void
    fileNameChanged(const QString &new_file_name, const QString &old_file_name);
    void updateDocumentTab(Document *document);

  Q_SIGNALS:
    void currentDocumentChanged(Document *document);
    void documentCloseRequested(int index);
    void enabledStandardActionsChanged();

  private:
    static QScopedPointer<DocumentManager> m_instance;

    std::vector<std::unique_ptr<Document>> m_documents;
    std::unordered_map<QString, DocumentEditor *> m_editor_for_document_id;

    QPointer<QWidget> m_widget;
    QWidget *m_no_document_widget;
    QTabBar *m_tab_bar;
    QStackedLayout *m_editor_stack;

    QScopedPointer<utils::QtFileSystemWatcher> m_file_system_watcher;
    QUndoGroup *m_undo_group;
  };

}// namespace flow::document

#endif//FLOW_DOCUMENT_MANAGER_H
