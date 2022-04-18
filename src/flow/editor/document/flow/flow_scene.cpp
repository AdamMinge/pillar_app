/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsSceneDragDropEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/commands/add_remove_node.h"
#include "flow/editor/document/flow/flow_document.h"
#include "flow/editor/document/flow/flow_scene.h"
/* -------------------------------------------------------------------------- */

FlowScene::FlowScene(QObject *parent)
    : QGraphicsScene(parent), m_flow_document(nullptr)
{}

FlowScene::~FlowScene() = default;

void FlowScene::setSceneDocument(FlowDocument *flow_document)
{
  if (m_flow_document == flow_document) return;

  m_flow_document = flow_document;
}

FlowDocument *FlowScene::getSceneDocument() const { return m_flow_document; }

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
    m_flow_document->getUndoStack()->push(new AddNodeCommand(this, data));
  } else if (mime_data->hasFormat(QLatin1String("flow/converter")))
  {
    const auto data = mime_data->data(QLatin1String("flow/converter"));
    // TODO Implementation
  }
}

bool FlowScene::isAcceptable(const QMimeData *mime_data) const
{
  if (
    mime_data->hasFormat(QLatin1String("flow/node")) ||
    mime_data->hasFormat(QLatin1String("flow/converter")))
    return true;

  return false;
}
