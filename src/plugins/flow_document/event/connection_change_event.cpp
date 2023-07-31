/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/connection_change_event.h"

#include "flow_document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ ConnectionEvent --------------------------- */

ConnectionEvent::ConnectionEvent(Event event, NodeLayer* connection_layer,
                                 qsizetype index)
    : ChangeEvent(type),
      m_event(event),
      m_node_layer(connection_layer),
      m_index(index) {}

ConnectionEvent::~ConnectionEvent() = default;

ConnectionEvent::Event ConnectionEvent::getEvent() const { return m_event; }

NodeLayer* ConnectionEvent::getNodeLayer() const { return m_node_layer; }

qsizetype ConnectionEvent::getIndex() const { return m_index; }

Connection* ConnectionEvent::getConnection() const {
  return m_node_layer->connectionAt(m_index);
}

/* --------------------------- ConnectionsChangeEvent ----------------------- */

ConnectionsChangeEvent::ConnectionsChangeEvent(QList<Connection*> connections,
                                               Properties properties)
    : ChangeEvent(type),
      m_connections(std::move(connections)),
      m_properties(properties) {}

ConnectionsChangeEvent::~ConnectionsChangeEvent() = default;

const QList<Connection*>& ConnectionsChangeEvent::getConnections() const {
  return m_connections;
}

ConnectionsChangeEvent::Properties ConnectionsChangeEvent::getProperties()
    const {
  return m_properties;
}

bool ConnectionsChangeEvent::contains(Connection* connection) const {
  return m_connections.contains(connection);
}

}  // namespace flow_document
