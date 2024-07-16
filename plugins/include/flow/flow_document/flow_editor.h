#ifndef FLOW_DOCUMENT_FLOW_EDITOR_H
#define FLOW_DOCUMENT_FLOW_EDITOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QPointer>
#include <QScopedPointer>
#include <QStackedWidget>
#include <QToolBar>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/document/document_editor.h>
#include <pillar/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {
class UndoDock;
}

namespace flow_document {

class FlowDocument;
class FlowView;

class Tool;
class ToolsBar;

class FactoriesDock;
class PropertiesDock;
class NodesDock;
class LayersDock;

class FlowDockWidget;
class FlowDockWidgetFactory;

class FlowDocumentActionHandler;

/* --------------------------------- FlowEditor ----------------------------- */

class FLOW_DOCUMENT_API FlowEditor
    : public pillar::DocumentEditor,
      public pillar::PluginListener<FlowDockWidgetFactory> {
  Q_OBJECT
  Q_INTERFACES(pillar::DocumentEditor)

 private:
  struct Preferences;

 public:
  explicit FlowEditor(QObject *parent = nullptr);
  ~FlowEditor() override;

  void setCurrentDocument(pillar::Document *document) override;

  void addDocument(pillar::Document *document) override;
  void removeDocument(pillar::Document *document) override;

  [[nodiscard]] pillar::Document *getCurrentDocument() const override;
  [[nodiscard]] QWidget *getEditorWidget() const override;

  void saveState() override;
  void restoreState() override;

  [[nodiscard]] QList<QDockWidget *> getDockWidgets() const override;
  [[nodiscard]] QList<qtils::QtDialogWithToggleView *> getDialogWidgets()
      const override;

  void performStandardAction(StandardAction standard_action) override;
  [[nodiscard]] StandardActions getEnabledStandardActions() const override;

  [[nodiscard]] QString getDocumentId() const override;

 protected:
  void addedObject(FlowDockWidgetFactory *factory) override;
  void removedObject(FlowDockWidgetFactory *factory) override;

 private Q_SLOTS:
  void toolSelected(Tool *tool);
  void cursorChanged(const QCursor &cursor);

 private:
  void initUi();
  void initConnections();

  void addDockWidget(QDockWidget *dock_widget, Qt::DockWidgetArea area);

 private:
  FlowDocument *m_current_document;
  QPointer<QMainWindow> m_main_window;

  ToolsBar *m_tools_bar;
  QStackedWidget *m_scene_stack;
  pillar::UndoDock *m_undo_dock;

  QHash<FlowDockWidgetFactory *, FlowDockWidget *> m_dock_widget_for_factory;

  FlowDocumentActionHandler &m_action_handler;

  QHash<FlowDocument *, FlowView *> m_view_for_document;

  QScopedPointer<Preferences> m_preferences;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_EDITOR_H
