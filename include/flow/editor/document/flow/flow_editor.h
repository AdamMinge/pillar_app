#ifndef FLOW_FLOW_EDITOR_H
#define FLOW_FLOW_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QPointer>
#include <QStackedWidget>
/* ----------------------------------- Api ---------------------------------- */
#include <flow/modules/api/document/document_editor.h>
/* -------------------------------------------------------------------------- */

class FlowDocument;

class UndoDock;
class FlowView;

class FlowEditor : public api::document::IDocumentEditor
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit FlowEditor(QObject *parent = nullptr);
  ~FlowEditor() override;

  void setCurrentDocument(api::document::IDocument *document) override;

  void addDocument(api::document::IDocument *document) override;
  void removeDocument(api::document::IDocument *document) override;

  [[nodiscard]] api::document::IDocument *getCurrentDocument() const override;
  [[nodiscard]] QWidget *getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget *> getDockWidgets() const override;
  [[nodiscard]] QList<utils::QtDialogWithToggleView *>
  getDialogWidgets() const override;

  void performStandardAction(StandardAction standard_action) override;
  [[nodiscard]] StandardActions getEnabledStandardActions() const override;

private:
  FlowDocument *m_current_document;
  QPointer<QMainWindow> m_main_window;

  QStackedWidget *m_scene_stack;
  UndoDock *m_undo_dock;

  QHash<FlowDocument *, FlowView *> m_view_for_document;

  QScopedPointer<Preferences> m_preferences;
};

#endif//FLOW_FLOW_EDITOR_H
