/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document.h"

#include "flow_document/event/objects_event.h"
#include "flow_document/flow/flow_graph.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

std::unique_ptr<egnite::Document> FlowDocument::create() {
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent),
      m_graph(new FlowGraph(this)) {}

FlowDocument::~FlowDocument() = default;

const FlowGraph *FlowDocument::getGraph() const { return m_graph; }

FlowGraph *FlowDocument::getGraph() { return m_graph; }
/*
void FlowDocument::addNode(Node *node) {
  m_nodes.append(node);
  Q_EMIT event(ObjectsAddedEvent(node, ObjectsAddedEvent::ObjectsType::Node));
}

void FlowDocument::removeNode(Node *node) {
  m_nodes.removeOne(node);
  Q_EMIT event(ObjectsRemovedEvent(node, ObjectsAddedEvent::ObjectsType::Node));
}
*/
}  // namespace flow_document