#ifndef FLOW_INTERFACE_DOCUMENT_EDITOR_H
#define FLOW_INTERFACE_DOCUMENT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QObject>
/* -------------------------------------------------------------------------- */

namespace utils
{
  class QtDialogWithToggleView;
}

namespace api::document
{
  class IDocument;

  class IDocumentEditor : public QObject
  {
    Q_OBJECT

  public:
    enum StandardAction
    {
      CutAction = 0x01,
      CopyAction = 0x02,
      PasteAction = 0x04,
      DeleteAction = 0x08
    };
    Q_DECLARE_FLAGS(StandardActions, StandardAction)
    Q_FLAG(StandardActions)

  public:
    explicit IDocumentEditor(QObject *parent = nullptr);
    ~IDocumentEditor() override;

    virtual void setCurrentDocument(api::document::IDocument *document) = 0;

    virtual void addDocument(api::document::IDocument *document) = 0;
    virtual void removeDocument(api::document::IDocument *document) = 0;

    [[nodiscard]] virtual api::document::IDocument *
    getCurrentDocument() const = 0;
    [[nodiscard]] virtual QWidget *getEditorWidget() const = 0;

    virtual void saveState() = 0;
    virtual void restoreState() = 0;

    [[nodiscard]] virtual QList<QDockWidget *> getDockWidgets() const = 0;
    [[nodiscard]] virtual QList<utils::QtDialogWithToggleView *>
    getDialogWidgets() const = 0;

    virtual void performStandardAction(StandardAction standard_action) = 0;
    [[nodiscard]] virtual StandardActions getEnabledStandardActions() const = 0;

  Q_SIGNALS:
    void enabledStandardActionsChanged();
  };
}// namespace api::document

#endif//FLOW_INTERFACE_DOCUMENT_EDITOR_H
