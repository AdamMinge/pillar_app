/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_editor.h"

#include "flow_document/component/node/flow_nodes_dock.h"
#include "flow_document/component/scene/flow_abstract_tool.h"
#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/flow_tools_bar.h"
#include "flow_document/component/scene/flow_view.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/document/undo_dock.h>
#include <egnite/preferences_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- Preferences ----------------------------- */

struct FlowEditor::Preferences {
  egnite::Preference<QSize> editor_size =
      egnite::Preference<QSize>(QString("flow_editor/size"));
  egnite::Preference<QByteArray> editor_state =
      egnite::Preference<QByteArray>(QString("flow_editor/state"));
};

/* -------------------------------- SceneEditor ----------------------------- */

FlowEditor::FlowEditor(QObject *parent)
    : egnite::DocumentEditor(parent),
      m_current_document(nullptr),
      m_main_window(new QMainWindow()),
      m_tools_bar(new FlowToolsBar(m_main_window)),
      m_scene_stack(new QStackedWidget(m_main_window)),
      m_nodes_dock(new FlowNodesDock(m_main_window)),
      m_undo_dock(new egnite::UndoDock(m_main_window)),
      m_preferences(new Preferences) {
  initUi();
  initConnections();
}

FlowEditor::~FlowEditor() = default;

void FlowEditor::setCurrentDocument(egnite::Document *document) {
  if (m_current_document == document) return;

  auto flow_document = qobject_cast<FlowDocument *>(document);
  Q_ASSERT(flow_document || !document);

  m_current_document = flow_document;

  if (m_current_document) m_undo_dock->setStack(flow_document->getUndoStack());

  m_tools_bar->setDocument(m_current_document);
  if (auto flow_view = m_view_for_document[flow_document]; flow_view) {
    m_scene_stack->setCurrentWidget(flow_view);
    toolSelected(m_tools_bar->getSelectedTool());
  }
}

void FlowEditor::addDocument(egnite::Document *document) {
  auto flow_document = dynamic_cast<FlowDocument *>(document);
  Q_ASSERT(flow_document);

  auto view = new FlowView(m_scene_stack);
  auto scene = new FlowScene(view);

  scene->setSceneDocument(flow_document);
  view->setScene(scene);
  view->setAcceptDrops(true);

  m_view_for_document.insert(flow_document, view);

  m_scene_stack->addWidget(view);
}

void FlowEditor::removeDocument(egnite::Document *document) {
  auto flow_document = dynamic_cast<FlowDocument *>(document);
  Q_ASSERT(flow_document);
  Q_ASSERT(m_view_for_document.contains(flow_document));

  if (flow_document == m_current_document) setCurrentDocument(nullptr);

  auto view = m_view_for_document.take(flow_document);
  m_scene_stack->removeWidget(view);

  view->deleteLater();
}

egnite::Document *FlowEditor::getCurrentDocument() const {
  return m_current_document;
}

QWidget *FlowEditor::getEditorWidget() const { return m_main_window; }

void FlowEditor::saveState() {
  m_preferences->editor_state = m_main_window->saveState();
  m_preferences->editor_size = m_main_window->size();
}

void FlowEditor::restoreState() {
  auto editor_size = static_cast<QSize>(m_preferences->editor_size);
  auto editor_state = static_cast<QByteArray>(m_preferences->editor_state);

  if (!editor_size.isNull()) m_main_window->resize(editor_size);
  if (!editor_state.isNull()) m_main_window->restoreState(editor_state);
}

QList<QDockWidget *> FlowEditor::getDockWidgets() const {
  return QList<QDockWidget *>{m_undo_dock, m_nodes_dock};
}

QList<utils::QtDialogWithToggleView *> FlowEditor::getDialogWidgets() const {
  return QList<utils::QtDialogWithToggleView *>{};
}

void FlowEditor::performStandardAction(StandardAction standard_action) {
  // TODO : implementation //
}

FlowEditor::StandardActions FlowEditor::getEnabledStandardActions() const {
  // TODO : implementation //
  FlowEditor::StandardActions standard_actions;
  return standard_actions;
}

QString FlowEditor::getDocumentId() const {
  return QLatin1String("FlowDocument");
}

void FlowEditor::toolSelected(FlowAbstractTool *tool) {
  auto flow_view = m_view_for_document[m_current_document];
  auto flow_scene = flow_view->getScene();
  auto prev_tool = flow_scene->getTool();

  if (prev_tool) {
    disconnect(prev_tool, &FlowAbstractTool::cursorChanged, this,
               &FlowEditor::cursorChanged);
  }

  flow_scene->setTool(tool);
  flow_view->viewport()->setCursor(tool ? tool->getCursor() : Qt::ArrowCursor);

  if (tool) {
    connect(tool, &FlowAbstractTool::cursorChanged, this,
            &FlowEditor::cursorChanged);
  }
}

void FlowEditor::cursorChanged(const QCursor &cursor) {
  auto flow_view = m_view_for_document[m_current_document];
  flow_view->viewport()->setCursor(cursor);
}

void FlowEditor::initUi() {
  m_main_window->setDockOptions(m_main_window->dockOptions() |
                                QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);
  m_main_window->setCentralWidget(m_scene_stack);

  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_undo_dock);
  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_nodes_dock);
  m_nodes_dock->raise();

  m_main_window->addToolBar(m_tools_bar);
}

void FlowEditor::initConnections() {
  connect(m_tools_bar, &FlowToolsBar::toolSelected, this,
          &FlowEditor::toolSelected);
}

}  // namespace flow_document