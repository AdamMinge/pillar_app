#ifndef FLOW_DOCUMENT_EDITOR_H
#define FLOW_DOCUMENT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QObject>
/* -------------------------------------------------------------------------- */

namespace api
{
  class IDocument;
}

namespace utils
{
  class QtDialogWithToggleView;
}

class DocumentEditor : public QObject
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
  ~DocumentEditor() override;

  virtual void setCurrentDocument(api::IDocument *document) = 0;

  virtual void addDocument(api::IDocument *document) = 0;
  virtual void removeDocument(api::IDocument *document) = 0;

  [[nodiscard]] virtual api::IDocument *getCurrentDocument() const = 0;
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

protected:
  explicit DocumentEditor(QObject *parent = nullptr);
};

#endif//FLOW_DOCUMENT_EDITOR_H
