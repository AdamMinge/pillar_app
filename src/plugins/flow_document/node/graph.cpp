/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/graph.h"

#include "flow_document/node/node.h"
#include "flow_document/node/node_factory.h"
#include "flow_document/node/pin_connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Graph::Graph(QObject *parent) : QObject(parent) {}

Graph::~Graph() = default;

QUuid Graph::addNode(const QString &node_type) {
  auto factory = findFactory(node_type);
  if (!factory) return {};

  auto node = factory->create();
  auto node_id = QUuid::createUuid();

  auto iter = m_nodes.emplace(std::move(node_id), std::move(node));
  return iter.first->first;
}

bool Graph::removeNode(const QUuid &node_id) {
  if (!m_nodes.contains(node_id)) return false;

  m_nodes.erase(node_id);
  return true;
}

const Node &Graph::getNode(const QUuid &node_id) const {
  return *m_nodes.at(node_id);
}

const Node *Graph::findNode(const QUuid &node_id) const {
  if (!m_nodes.contains(node_id)) return nullptr;
  return m_nodes.at(node_id).get();
}

QUuid Graph::addConnection(const QUuid &out_node_id, size_t out_pin_id,
                           const QUuid &in_node_id, size_t in_pin_id) {
  if (!m_nodes.contains(out_node_id)) return {};
  if (!m_nodes.contains(in_node_id)) return {};

  auto &out_node = m_nodes.at(out_node_id);
  auto &in_node = m_nodes.at(in_node_id);

  if (out_node->getPinsCounts(Pin::Type::Out) <= out_pin_id) return {};
  if (in_node->getPinsCounts(Pin::Type::In) <= in_pin_id) return {};

  auto &out_pin = out_node->getPin(Pin::Type::Out, out_pin_id);
  auto &in_pin = in_node->getPin(Pin::Type::In, in_pin_id);

  auto pin_connection = std::make_unique<PinConnection>(out_pin, in_pin);
  auto connection_id = QUuid::createUuid();

  auto iter = m_connections.emplace(std::move(connection_id),
                                    std::move(pin_connection));
  return iter.first->first;
}

bool Graph::removeConnection(const QUuid &connection_id) {
  if (!m_connections.contains(connection_id)) return false;

  m_connections.erase(connection_id);
  return true;
}

const PinConnection &Graph::getConnection(const QUuid &connection_id) const {
  return *m_connections.at(connection_id);
}

const PinConnection *Graph::findConnection(const QUuid &connection_id) const {
  if (!m_connections.contains(connection_id)) return nullptr;
  return m_connections.at(connection_id).get();
}

void Graph::addedObject(NodeFactories *factories) {
  m_node_factories.insert(factories);
}

void Graph::removedObject(NodeFactories *factories) {
  if (m_node_factories.contains(factories)) m_node_factories.erase(factories);
}

NodeFactory *Graph::findFactory(const QString &node_type) {
  for (auto node_factories : m_node_factories)
    if (auto factory = node_factories->getFactory(node_type); factory)
      return factory;

  return nullptr;
}

}  // namespace flow_document
