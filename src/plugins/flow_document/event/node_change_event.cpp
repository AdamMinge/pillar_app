/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/node_change_event.h"

#include "flow_document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- NodeEvent ------------------------------ */

NodeEvent::NodeEvent(Type type, NodeLayer* node_layer, qsizetype index)
    : ChangeEvent(type), m_node_layer(node_layer), m_index(index) {}

NodeEvent::~NodeEvent() = default;

NodeLayer* NodeEvent::getNodeLayer() const { return m_node_layer; }

qsizetype NodeEvent::getIndex() const { return m_index; }

Node* NodeEvent::getNode() const { return m_node_layer->at(m_index); }

/* ---------------------------------- NodesEvent ---------------------------- */

NodesEvent::NodesEvent(Type type, QList<Node*> nodes)
    : ChangeEvent(type), m_nodes(std::move(nodes)) {}

NodesEvent::~NodesEvent() = default;

const QList<Node*>& NodesEvent::getNodes() const { return m_nodes; }

/* ------------------------------ NodesChangeEvent -------------------------- */

NodesChangeEvent::NodesChangeEvent(QList<Node*> nodes, Properties properties)
    : NodesEvent(Type::NodesChanged, std::move(nodes)),
      m_properties(properties) {}

NodesChangeEvent::~NodesChangeEvent() = default;

NodesChangeEvent::Properties NodesChangeEvent::getProperties() const {
  return m_properties;
}

}  // namespace flow_document
