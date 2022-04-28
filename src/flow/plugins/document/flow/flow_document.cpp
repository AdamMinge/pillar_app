/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_document.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/node.h>
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::document::Document> FlowDocument::create()
{
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent)
{}

FlowDocument::~FlowDocument()
{
  for (auto &node : m_nodes)
    if (node) node->deleteLater();
}

void FlowDocument::addNode(flow::node::Node *node)
{
  m_nodes.append(QPointer<flow::node::Node>(node));
  Q_EMIT addedNode(node);
}

void FlowDocument::removeNode(flow::node::Node *node)
{
  m_nodes.removeOne(node);
  Q_EMIT removedNode(node);
  node->deleteLater();
}
