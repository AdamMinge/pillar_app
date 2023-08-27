/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/connection.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ ConnectionSide ---------------------------- */

ConnectionSide::ConnectionSide(QUuid node_id, size_t pin_id)
    : m_node_id(std::move(node_id)), m_pin_id(pin_id) {}

ConnectionSide::~ConnectionSide() = default;

void ConnectionSide::setNodeId(const QUuid &id) { m_node_id = id; }

QUuid ConnectionSide::getNodeId() const { return m_node_id; }

void ConnectionSide::setPinId(size_t id) { m_pin_id = id; }

size_t ConnectionSide::getPinId() const { return m_pin_id; }

void ConnectionSide::serialize(utils::OArchive &archive) const {
  archive << utils::ArchiveProperty("node", m_node_id);
  archive << utils::ArchiveProperty("pin", m_pin_id);
}

void ConnectionSide::deserialize(utils::IArchive &archive) {
  archive >> utils::ArchiveProperty("node", m_node_id);
  archive >> utils::ArchiveProperty("pin", m_pin_id);
}

bool ConnectionSide::operator==(const ConnectionSide &other) const {
  return m_node_id == other.m_node_id && m_pin_id == other.m_pin_id;
}

bool ConnectionSide::operator!=(const ConnectionSide &other) const {
  return m_node_id != other.m_node_id || m_pin_id != other.m_pin_id;
}

/* --------------------------------- Connection ----------------------------- */

Connection::Connection() : m_visible(true) {}

Connection::~Connection() = default;

void Connection::setOutputSide(ConnectionSide connection_side) {
  m_output_side = std::move(connection_side);
}

void Connection::setInputSide(ConnectionSide connection_side) {
  m_input_side = std::move(connection_side);
}

const ConnectionSide &Connection::getOutputSide() const {
  return m_output_side;
}

const ConnectionSide &Connection::getInputSide() const { return m_input_side; }

void Connection::setVisible(bool visible) { m_visible = visible; }

bool Connection::isVisible() const { return m_visible; }

NodeLayer *Connection::getParent() const { return m_parent; }

std::unique_ptr<Connection> Connection::clone() const {
  auto connection = std::make_unique<Connection>();
  connection->init(this);
  return std::move(connection);
}

void Connection::serialize(utils::OArchive &archive) const {
  Object::serialize(archive);

  archive << utils::ArchiveProperty("visible", m_visible);
  archive << utils::ArchiveProperty("output", m_output_side);
  archive << utils::ArchiveProperty("input", m_input_side);
}

void Connection::deserialize(utils::IArchive &archive) {
  Object::deserialize(archive);

  archive >> utils::ArchiveProperty("visible", m_visible);
  archive >> utils::ArchiveProperty("output", m_output_side);
  archive >> utils::ArchiveProperty("input", m_input_side);
}

void Connection::init(const Connection *connection) {
  Object::init(connection);

  m_visible = connection->m_visible;
  m_input_side = connection->m_input_side;
  m_output_side = connection->m_output_side;
}

void Connection::setParent(NodeLayer *parent) { m_parent = parent; }

}  // namespace flow_document
