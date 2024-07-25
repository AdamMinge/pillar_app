/* ----------------------------------- Local -------------------------------- */
#include "flow/document/event/node_change_event.h"

#include "flow/document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------------- NodeEvent ------------------------------ */

NodeEvent::NodeEvent(Event event, NodeLayer* node_layer, qsizetype index)
    : ChangeEvent(type),
      m_event(event),
      m_node_layer(node_layer),
      m_index(index) {}

NodeEvent::~NodeEvent() = default;

NodeEvent::Event NodeEvent::getEvent() const { return m_event; }

NodeLayer* NodeEvent::getNodeLayer() const { return m_node_layer; }

qsizetype NodeEvent::getIndex() const { return m_index; }

Node* NodeEvent::getNode() const { return m_node_layer->nodeAt(m_index); }

/* ------------------------------ NodesChangeEvent -------------------------- */

NodesChangeEvent::NodesChangeEvent(QList<Node*> nodes, Properties properties)
    : ChangeEvent(type), m_nodes(std::move(nodes)), m_properties(properties) {}

NodesChangeEvent::~NodesChangeEvent() = default;

const QList<Node*>& NodesChangeEvent::getNodes() const { return m_nodes; }

NodesChangeEvent::Properties NodesChangeEvent::getProperties() const {
  return m_properties;
}

bool NodesChangeEvent::contains(Node* node) const {
  return m_nodes.contains(node);
}

}  // namespace flow
