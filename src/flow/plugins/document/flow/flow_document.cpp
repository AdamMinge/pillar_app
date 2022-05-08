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

FlowDocument::~FlowDocument() { qDeleteAll(m_nodes); }

void FlowDocument::addNode(flow::node::Node *node)
{
  m_nodes.append(node);
  Q_EMIT nodeAdded(node);
}

void FlowDocument::removeNode(flow::node::Node *node)
{
  m_nodes.removeOne(node);
  Q_EMIT nodeRemoved(node);
  node->deleteLater();
}
