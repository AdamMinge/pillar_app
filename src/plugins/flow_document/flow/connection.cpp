/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/connection.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

Connection::Connection() : m_visible(true) {}

Connection::~Connection() = default;

void Connection::setVisible(bool visible) { m_visible = visible; }

bool Connection::isVisible() const { return m_visible; }

ConnectionLayer *Connection::getParent() const { return m_parent; }

std::unique_ptr<Connection> Connection::clone() const {
  auto connection = std::make_unique<Connection>();
  connection->init(this);
  return std::move(connection);
}

void Connection::serialize(utils::OArchive &archive) const {
  Object::serialize(archive);

  archive << utils::ArchiveProperty("visible", m_visible);
}

void Connection::deserialize(utils::IArchive &archive) {
  Object::deserialize(archive);

  archive >> utils::ArchiveProperty("visible", m_visible);
}

void Connection::init(const Connection *connection) {
  Object::init(connection);

  m_visible = connection->m_visible;
}

void Connection::setParent(ConnectionLayer *parent) { m_parent = parent; }

}  // namespace flow_document
