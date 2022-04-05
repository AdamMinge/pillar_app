#ifndef FLOW_INTERFACE_DOCUMENT_MANAGER_H
#define FLOW_INTERFACE_DOCUMENT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QUndoGroup>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <vector>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/api/document/document.h"
/* -------------------------------------------------------------------------- */

namespace api::document
{

  class IDocumentEditor;

  class IDocumentManager : public QObject
  {
    Q_OBJECT

  public:
    explicit IDocumentManager(QObject *parent = nullptr);
    ~IDocumentManager() override;

    [[nodiscard]] virtual QWidget *getWidget() const = 0;

    virtual void addEditor(
      api::document::IDocument::Type document_type,
      std::unique_ptr<api::document::IDocumentEditor> editor) = 0;
    virtual void removeEditor(api::document::IDocument::Type document_type) = 0;
    virtual void removeAllEditors() = 0;

    [[nodiscard]] virtual api::document::IDocumentEditor *
    getEditor(api::document::IDocument::Type document_type) const = 0;
    [[nodiscard]] virtual api::document::IDocumentEditor *
    getCurrentEditor() const = 0;

    virtual void
    addDocument(std::unique_ptr<api::document::IDocument> document) = 0;
    virtual void insertDocument(
      int index, std::unique_ptr<api::document::IDocument> document) = 0;

    virtual void removeDocument(int index) = 0;
    virtual void removeAllDocuments() = 0;

    [[nodiscard]] virtual api::document::IDocument *
    getDocument(int index) const = 0;
    [[nodiscard]] virtual api::document::IDocument *
    getCurrentDocument() const = 0;

    [[nodiscard]] virtual int
    findDocument(api::document::IDocument *document) const = 0;
    [[nodiscard]] virtual int findDocument(const QString &file_name) const = 0;

    virtual void switchToDocument(int index) = 0;
    virtual void switchToDocument(api::document::IDocument *document) = 0;
    virtual bool switchToDocument(const QString &file_name) = 0;

    [[nodiscard]] virtual QUndoGroup *getUndoGroup() const = 0;

    virtual void saveState() = 0;
    virtual void restoreState() = 0;

    virtual bool saveDocument(api::document::IDocument *document) = 0;
    virtual bool saveDocumentAs(api::document::IDocument *document) = 0;

    virtual bool reloadDocumentAt(int index) = 0;
    virtual bool loadDocument(const QString &file_name) = 0;

    [[nodiscard]] virtual const std::vector<
      std::unique_ptr<api::document::IDocument>> &
    getDocuments() const = 0;

  Q_SIGNALS:
    void currentDocumentChanged(api::document::IDocument *document);
    void documentCloseRequested(int index);
  };

}// namespace api::document

#endif//FLOW_INTERFACE_DOCUMENT_MANAGER_H
