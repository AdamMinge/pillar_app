#ifndef PLUGIN_FLOW_FLOW_EDITOR_H
#define PLUGIN_FLOW_FLOW_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QPointer>
#include <QStackedWidget>
#include <QToolBar>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/document_editor.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::document
{
  class UndoDock;
}

class FlowDocument;

class FlowNodesDock;
class FlowConvertersDock;
class FlowAbstractTool;
class FlowView;

class FLOW_DOCUMENT_API FlowEditor : public flow::document::DocumentEditor
{
  Q_OBJECT
  Q_INTERFACES(flow::document::DocumentEditor)

private:
  struct Preferences;

public:
  explicit FlowEditor(QObject *parent = nullptr);
  ~FlowEditor() override;

  void setCurrentDocument(flow::document::Document *document) override;

  void addDocument(flow::document::Document *document) override;
  void removeDocument(flow::document::Document *document) override;

  [[nodiscard]] flow::document::Document *getCurrentDocument() const override;
  [[nodiscard]] QWidget *getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget *> getDockWidgets() const override;
  [[nodiscard]] QList<utils::QtDialogWithToggleView *>
  getDialogWidgets() const override;

  void performStandardAction(StandardAction standard_action) override;
  [[nodiscard]] StandardActions getEnabledStandardActions() const override;

  [[nodiscard]] QString getDocumentId() const override;

private Q_SLOTS:
  void toolSelected(FlowAbstractTool *tool);

private:
  void initUi();
  void initConnections();

private:
  FlowDocument *m_current_document;
  QPointer<QMainWindow> m_main_window;

  QToolBar *m_tool_bar;
  QStackedWidget *m_scene_stack;
  FlowNodesDock *m_nodes_dock;
  FlowConvertersDock *m_converters_dock;
  flow::document::UndoDock *m_undo_dock;

  QHash<FlowDocument *, FlowView *> m_view_for_document;

  QScopedPointer<Preferences> m_preferences;
};

#endif//PLUGIN_FLOW_FLOW_EDITOR_H
