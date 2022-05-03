/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_scene.h"
#include "flow/plugins/document/flow/command/add_remove_node.h"
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
#include "flow/plugins/document/flow/component/tool/flow_abstract_tool.h"
#include "flow/plugins/document/flow/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsSceneDragDropEvent>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/node.h>
/* -------------------------------------------------------------------------- */

FlowScene::FlowScene(QObject *parent)
    : QGraphicsScene(parent), m_flow_document(nullptr), m_flow_tool(nullptr)
{
  setItemIndexMethod(QGraphicsScene::NoIndex);
}

FlowScene::~FlowScene() = default;

void FlowScene::setSceneDocument(FlowDocument *flow_document)
{
  if (m_flow_document == flow_document) return;

  if (m_flow_document)
  {
    disconnect(
      m_flow_document, &FlowDocument::nodeAdded, this, &FlowScene::nodeAdded);
    disconnect(
      m_flow_document, &FlowDocument::nodeRemoved, this,
      &FlowScene::nodeRemoved);
  }

  m_flow_document = flow_document;

  if (m_flow_document)
  {
    connect(
      m_flow_document, &FlowDocument::nodeAdded, this, &FlowScene::nodeAdded);
    connect(
      m_flow_document, &FlowDocument::nodeRemoved, this,
      &FlowScene::nodeRemoved);
  }
}

FlowDocument *FlowScene::getSceneDocument() const { return m_flow_document; }

void FlowScene::setTool(FlowAbstractTool *tool)
{
  if (m_flow_tool == tool) return;

  if (m_flow_tool) m_flow_tool->deactivate(this);

  m_flow_tool = tool;

  if (m_flow_tool) m_flow_tool->activate(this);
}

FlowAbstractTool *FlowScene::getTool() const { return m_flow_tool; }

void FlowScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
  auto mime_data = event->mimeData();
  event->setAccepted(isAcceptable(mime_data));
}

void FlowScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
  auto mime_data = event->mimeData();
  event->setAccepted(isAcceptable(mime_data));
}

void FlowScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
  auto mime_data = event->mimeData();
  if (mime_data->hasFormat(QLatin1String("flow/node")))
  {
    const auto data = mime_data->data(QLatin1String("flow/node"));
    for (auto &node_id : data.split(';'))
      m_flow_document->getUndoStack()->push(
        new AddNodeCommand(m_flow_document, node_id, event->scenePos()));

  } else if (mime_data->hasFormat(QLatin1String("flow/type_converter")))
  {
    // TODO Implementation
  }
}

void FlowScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  QGraphicsScene::mouseMoveEvent(mouseEvent);

  if (m_flow_tool)
  {
    mouseEvent->accept();
    m_flow_tool->mouseMoved(mouseEvent);
  }
}

void FlowScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  QGraphicsScene::mousePressEvent(mouseEvent);

  if (m_flow_tool)
  {
    mouseEvent->accept();
    m_flow_tool->mousePressed(mouseEvent);
  }
}

void FlowScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  QGraphicsScene::mouseReleaseEvent(mouseEvent);

  if (m_flow_tool)
  {
    mouseEvent->accept();
    m_flow_tool->mouseReleased(mouseEvent);
  }
}

void FlowScene::nodeAdded(flow::node::Node *node)
{
  auto node_item = std::make_unique<FlowNodeItem>(*node);
  m_node_items.insert(node, node_item.get());
  addItem(node_item.release());
}

void FlowScene::nodeRemoved(flow::node::Node *node)
{
  Q_ASSERT(m_node_items.contains(node));
  removeItem(m_node_items[node]);
  m_node_items.remove(node);
}

bool FlowScene::isAcceptable(const QMimeData *mime_data) const
{
  if (
    mime_data->hasFormat(QLatin1String("flow/node")) ||
    mime_data->hasFormat(QLatin1String("flow/type_converter")))
    return true;

  return false;
}
