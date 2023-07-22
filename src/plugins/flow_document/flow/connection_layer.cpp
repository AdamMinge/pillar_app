/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/connection_layer.h"

#include "flow_document/flow/connection.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

ConnectionLayer::ConnectionLayer() = default;

ConnectionLayer::~ConnectionLayer() = default;

void ConnectionLayer::append(std::unique_ptr<Connection> connection) {
  insert(m_connections.size(), std::move(connection));
}

void ConnectionLayer::insert(qsizetype index,
                             std::unique_ptr<Connection> connection) {
  Q_ASSERT(index >= 0 && index <= m_connections.size());
  auto insert_iter = m_connections.begin() + index;
  auto added_connection_iter =
      m_connections.insert(insert_iter, std::move(connection));

  (*added_connection_iter)->setParent(this);
}

void ConnectionLayer::remove(qsizetype index) { Q_UNUSED(take(index)); }

std::unique_ptr<Connection> ConnectionLayer::take(qsizetype index) {
  Q_ASSERT(index >= 0 && index < m_connections.size());
  auto take_iter = m_connections.begin() + index;
  auto connection = std::move(*take_iter);
  m_connections.erase(take_iter);

  connection->setParent(nullptr);
  return connection;
}

Connection* ConnectionLayer::at(qsizetype index) const {
  Q_ASSERT(index >= 0 && index < m_connections.size());
  return m_connections.at(index).get();
}

qsizetype ConnectionLayer::indexOf(Connection* connection) const {
  auto iter = std::find_if(m_connections.cbegin(), m_connections.cend(),
                           [connection](const auto& connection_ptr) {
                             return connection_ptr.get() == connection;
                           });

  if (iter != m_connections.end())
    return std::distance(m_connections.begin(), iter);

  return -1;
}

qsizetype ConnectionLayer::size() const { return m_connections.size(); }

ConnectionLayer::Connections::iterator ConnectionLayer::begin() {
  return m_connections.begin();
}

ConnectionLayer::Connections::iterator ConnectionLayer::end() {
  return m_connections.end();
}

ConnectionLayer::Connections::const_iterator ConnectionLayer::begin() const {
  return m_connections.begin();
}

ConnectionLayer::Connections::const_iterator ConnectionLayer::end() const {
  return m_connections.end();
}

std::unique_ptr<Layer> ConnectionLayer::clone() const {
  auto connection_layer = std::make_unique<ConnectionLayer>();
  connection_layer->init(this);
  return std::move(connection_layer);
}

void ConnectionLayer::serialize(utils::OArchive& archive) const {
  Layer::serialize(archive);

  archive << utils::ArchiveProperty("connections", m_connections);
}

void ConnectionLayer::deserialize(utils::IArchive& archive) {
  Layer::deserialize(archive);

  archive >> utils::ArchiveProperty("connections", m_connections);
  for (auto& connection : m_connections) connection->setParent(this);
}

void ConnectionLayer::init(const ConnectionLayer* connection_layer) {
  Layer::init(connection_layer);

  for (const auto& connection : *connection_layer) {
    append(connection->clone());
  }
}

}  // namespace flow_document
