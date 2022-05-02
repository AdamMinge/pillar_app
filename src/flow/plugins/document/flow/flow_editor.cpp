/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_editor.h"
#include "flow/plugins/document/flow/flow_document.h"
#include "flow/plugins/document/flow/flow_nodes_dock.h"
#include "flow/plugins/document/flow/flow_scene.h"
#include "flow/plugins/document/flow/flow_selection_tool.h"
#include "flow/plugins/document/flow/flow_tools_bar.h"
#include "flow/plugins/document/flow/flow_type_converters_dock.h"
#include "flow/plugins/document/flow/flow_view.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/undo_dock.h>
#include <flow/libflow/preferences_manager.h>
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct FlowEditor::Preferences {
  flow::Preference<QSize> editor_size =
    flow::Preference<QSize>(QString("flow_editor/size"));
  flow::Preference<QByteArray> editor_state =
    flow::Preference<QByteArray>(QString("flow_editor/state"));
};

/* -------------------------------- SceneEditor ----------------------------- */

FlowEditor::FlowEditor(QObject *parent)
    : flow::document::DocumentEditor(parent), m_current_document(nullptr),
      m_main_window(new QMainWindow()),
      m_tools_bar(new FlowToolsBar(m_main_window)),
      m_scene_stack(new QStackedWidget(m_main_window)),
      m_nodes_dock(new FlowNodesDock(m_main_window)),
      m_converters_dock(new FlowConvertersDock(m_main_window)),
      m_undo_dock(new flow::document::UndoDock(m_main_window)),
      m_preferences(new Preferences)
{
  initUi();
  initConnections();
}

FlowEditor::~FlowEditor() = default;

void FlowEditor::setCurrentDocument(flow::document::Document *document)
{
  if (m_current_document == document) return;

  auto flow_document = qobject_cast<FlowDocument *>(document);
  Q_ASSERT(flow_document || !document);

  m_current_document = flow_document;

  if (m_current_document) m_undo_dock->setStack(flow_document->getUndoStack());

  if (auto flow_view = m_view_for_document[flow_document]; flow_view)
  {
    m_scene_stack->setCurrentWidget(flow_view);
    auto scene = flow_view->getScene();
    scene->setTool(m_tools_bar->getSelectedTool());
  }
}

void FlowEditor::addDocument(flow::document::Document *document)
{
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

void FlowEditor::removeDocument(flow::document::Document *document)
{
  auto flow_document = dynamic_cast<FlowDocument *>(document);
  Q_ASSERT(flow_document);
  Q_ASSERT(m_view_for_document.contains(flow_document));

  if (flow_document == m_current_document) setCurrentDocument(nullptr);

  auto view = m_view_for_document.take(flow_document);
  m_scene_stack->removeWidget(view);

  view->deleteLater();
}

flow::document::Document *FlowEditor::getCurrentDocument() const
{
  return m_current_document;
}

QWidget *FlowEditor::getEditorWidget() const { return m_main_window; }

void FlowEditor::saveState()
{
  m_preferences->editor_state = m_main_window->saveState();
  m_preferences->editor_size = m_main_window->size();
}

void FlowEditor::restoreState()
{
  auto editor_size = static_cast<QSize>(m_preferences->editor_size);
  auto editor_state = static_cast<QByteArray>(m_preferences->editor_state);

  if (!editor_size.isNull()) m_main_window->resize(editor_size);
  if (!editor_state.isNull()) m_main_window->restoreState(editor_state);
}

QList<QDockWidget *> FlowEditor::getDockWidgets() const
{
  return QList<QDockWidget *>{m_undo_dock};
}

QList<utils::QtDialogWithToggleView *> FlowEditor::getDialogWidgets() const
{
  return QList<utils::QtDialogWithToggleView *>{};
}

void FlowEditor::performStandardAction(StandardAction standard_action)
{
  // TODO : implementation //
}

FlowEditor::StandardActions FlowEditor::getEnabledStandardActions() const
{
  // TODO : implementation //
  FlowEditor::StandardActions standard_actions;
  return standard_actions;
}

QString FlowEditor::getDocumentId() const
{
  return QLatin1String("FlowDocument");
}

void FlowEditor::toolSelected(FlowAbstractTool *tool)
{
  auto flow_view = m_view_for_document[m_current_document];
  auto flow_scene = flow_view->getScene();

  flow_scene->setTool(tool);
}

void FlowEditor::initUi()
{
  m_main_window->setDockOptions(
    m_main_window->dockOptions() | QMainWindow::GroupedDragging);
  m_main_window->setDockNestingEnabled(true);
  m_main_window->setCentralWidget(m_scene_stack);

  m_main_window->addDockWidget(Qt::LeftDockWidgetArea, m_undo_dock);
  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_nodes_dock);
  m_main_window->addDockWidget(Qt::RightDockWidgetArea, m_converters_dock);
  m_main_window->tabifyDockWidget(m_nodes_dock, m_converters_dock);
  m_nodes_dock->raise();

  m_main_window->addToolBar(m_tools_bar);
}

void FlowEditor::initConnections()
{
  connect(
    m_tools_bar, &FlowToolsBar::toolSelected, this, &FlowEditor::toolSelected);
}