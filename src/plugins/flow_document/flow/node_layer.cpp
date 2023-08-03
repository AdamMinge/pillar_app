/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/node_layer.h"

#include "flow_document/flow/node.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodeLayer::NodeLayer() = default;

NodeLayer::~NodeLayer() = default;

void NodeLayer::appendNode(std::unique_ptr<Node> node) {
  insertNode(m_nodes.size(), std::move(node));
}

void NodeLayer::insertNode(qsizetype index, std::unique_ptr<Node> node) {
  Q_ASSERT(index >= 0 && index <= m_nodes.size());
  auto insert_iter = m_nodes.begin() + index;
  auto added_node_iter = m_nodes.insert(insert_iter, std::move(node));

  (*added_node_iter)->setParent(this);
}

void NodeLayer::removeNode(qsizetype index) { Q_UNUSED(takeNode(index)); }

std::unique_ptr<Node> NodeLayer::takeNode(qsizetype index) {
  Q_ASSERT(index >= 0 && index < m_nodes.size());
  auto take_iter = m_nodes.begin() + index;
  auto node = std::move(*take_iter);
  m_nodes.erase(take_iter);

  node->setParent(nullptr);
  return node;
}

Node* NodeLayer::nodeAt(qsizetype index) const {
  Q_ASSERT(index >= 0 && index < m_nodes.size());
  return m_nodes.at(index).get();
}

qsizetype NodeLayer::indexOfNode(Node* node) const {
  auto iter = std::find_if(
      m_nodes.cbegin(), m_nodes.cend(),
      [node](const auto& node_ptr) { return node_ptr.get() == node; });

  if (iter != m_nodes.end()) return std::distance(m_nodes.begin(), iter);

  return -1;
}

qsizetype NodeLayer::nodesCount() const { return m_nodes.size(); }

void NodeLayer::appendConnection(std::unique_ptr<Connection> connection) {
  insertConnection(m_connections.size(), std::move(connection));
}

void NodeLayer::insertConnection(qsizetype index,
                                 std::unique_ptr<Connection> connection) {
  Q_ASSERT(index >= 0 && index <= m_connections.size());
  auto insert_iter = m_connections.begin() + index;
  auto added_connection_iter =
      m_connections.insert(insert_iter, std::move(connection));

  (*added_connection_iter)->setParent(this);
}

void NodeLayer::removeConnection(qsizetype index) {
  Q_UNUSED(takeConnection(index));
}

std::unique_ptr<Connection> NodeLayer::takeConnection(qsizetype index) {
  Q_ASSERT(index >= 0 && index < m_connections.size());
  auto take_iter = m_connections.begin() + index;
  auto connection = std::move(*take_iter);
  m_connections.erase(take_iter);

  connection->setParent(nullptr);
  return connection;
}

Connection* NodeLayer::connectionAt(qsizetype index) const {
  Q_ASSERT(index >= 0 && index < m_connections.size());
  return m_connections.at(index).get();
}

qsizetype NodeLayer::indexOfConnection(Connection* connection) const {
  auto iter = std::find_if(m_connections.cbegin(), m_connections.cend(),
                           [connection](const auto& connection_ptr) {
                             return connection_ptr.get() == connection;
                           });

  if (iter != m_connections.end())
    return std::distance(m_connections.begin(), iter);

  return -1;
}

qsizetype NodeLayer::connectionsCount() const { return m_connections.size(); }

QList<Connection*> NodeLayer::getNodeConnections(Node* node) const {
  if (!node) return {};

  auto connections = QList<Connection*>{};
  for (auto& connection : m_connections) {
    auto output_connected =
        connection->getOutputSide().getNodeId() == node->getId();
    auto input_connected =
        connection->getInputSide().getNodeId() == node->getId();

    if (output_connected || input_connected) {
      connections.append(connection.get());
    }
  }

  return connections;
}

QList<Node*> NodeLayer::getConnectionNodes(Connection* connection) const {
  if (!connection) return {};

  auto nodes = QList<Node*>{};
  for (auto& node : m_nodes) {
    auto output_connected =
        connection->getOutputSide().getNodeId() == node->getId();
    auto input_connected =
        connection->getInputSide().getNodeId() == node->getId();

    if (output_connected || input_connected) {
      nodes.append(node.get());
    }
  }

  return nodes;
}

std::unique_ptr<Layer> NodeLayer::clone() const {
  auto node_layer = std::make_unique<NodeLayer>();
  node_layer->init(this);
  return std::move(node_layer);
}

void NodeLayer::serialize(utils::OArchive& archive) const {
  Layer::serialize(archive);

  archive << utils::ArchiveProperty("nodes", m_nodes);
  archive << utils::ArchiveProperty("connections", m_connections);
}

void NodeLayer::deserialize(utils::IArchive& archive) {
  Layer::deserialize(archive);

  archive >> utils::ArchiveProperty("nodes", m_nodes);
  archive >> utils::ArchiveProperty("connections", m_connections);

  for (auto& node : m_nodes) node->setParent(this);
  for (auto& connection : m_connections) connection->setParent(this);
}

void NodeLayer::init(const NodeLayer* node_layer) {
  Layer::init(node_layer);

  for (const auto& node : node_layer->m_nodes) {
    appendNode(node->clone());
  }
  for (const auto& connection : node_layer->m_connections) {
    appendConnection(connection->clone());
  }
}

}  // namespace flow_document
