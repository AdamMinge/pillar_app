#ifndef PILLAR_DOCUMENT_EDITOR_H
#define PILLAR_DOCUMENT_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
class QtDialogWithToggleView;
}

namespace pillar {

class Document;

class LIB_PILLAR_API DocumentEditor : public QObject {
  Q_OBJECT

 public:
  enum class StandardAction {
    CutAction = 1 << 0,
    CopyAction = 1 << 1,
    PasteAction = 1 << 2,
    DeleteAction = 1 << 3,
  };
  Q_DECLARE_FLAGS(StandardActions, StandardAction)
  Q_FLAG(StandardActions)

 public:
  explicit DocumentEditor(QObject *parent = nullptr);
  ~DocumentEditor() override;

  virtual void setCurrentDocument(Document *document) = 0;

  virtual void addDocument(Document *document) = 0;
  virtual void removeDocument(Document *document) = 0;

  [[nodiscard]] virtual Document *getCurrentDocument() const = 0;
  [[nodiscard]] virtual QWidget *getEditorWidget() const = 0;

  virtual void saveState() = 0;
  virtual void restoreState() = 0;

  [[nodiscard]] virtual QList<QDockWidget *> getDockWidgets() const = 0;
  [[nodiscard]] virtual QList<qtils::QtDialogWithToggleView *>
  getDialogWidgets() const = 0;

  virtual void performStandardAction(StandardAction standard_action) = 0;
  [[nodiscard]] virtual StandardActions getEnabledStandardActions() const = 0;

  [[nodiscard]] virtual QString getDocumentId() const = 0;

 Q_SIGNALS:
  void enabledStandardActionsChanged();
};

}  // namespace pillar

Q_DECLARE_OPERATORS_FOR_FLAGS(pillar::DocumentEditor::StandardActions)
Q_DECLARE_INTERFACE(pillar::DocumentEditor, "org.pillar.DocumentEditor")

#endif  // PILLAR_DOCUMENT_EDITOR_H
