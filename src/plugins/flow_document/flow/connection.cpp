/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/connection.h"

#include "flow_document/flow/connection_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Connection::Connection() = default;

Connection::~Connection() = default;

ConnectionLayer *Connection::getParent() const { return m_parent; }

std::unique_ptr<Connection> Connection::clone() const {
  auto connection = std::make_unique<Connection>();
  connection->init(this);
  return std::move(connection);
}

void Connection::serialize(utils::OArchive &archive) const {
  Object::serialize(archive);
}

void Connection::deserialize(utils::IArchive &archive) {
  Object::deserialize(archive);
}

void Connection::init(const Connection *connection) {
  Object::init(connection);
}

void Connection::setParent(ConnectionLayer *parent) { m_parent = parent; }

}  // namespace flow_document
