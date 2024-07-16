/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/connection.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/archive.h>
#include <qtils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ ConnectionSide ---------------------------- */

ConnectionSide::ConnectionSide(QUuid node_id, size_t pin_id)
    : m_node_id(std::move(node_id)), m_pin_id(pin_id) {}

ConnectionSide::~ConnectionSide() = default;

bool ConnectionSide::isNull() const {
  return m_node_id.isNull() || m_pin_id < 0;
}

void ConnectionSide::setNodeId(const QUuid &id) { m_node_id = id; }

QUuid ConnectionSide::getNodeId() const { return m_node_id; }

void ConnectionSide::setPinId(size_t id) { m_pin_id = id; }

size_t ConnectionSide::getPinId() const { return m_pin_id; }

void ConnectionSide::serialize(qtils::OArchive &archive) const {
  archive << qtils::ArchiveProperty("node", m_node_id);
  archive << qtils::ArchiveProperty("pin", m_pin_id);
}

void ConnectionSide::deserialize(qtils::IArchive &archive) {
  archive >> qtils::ArchiveProperty("node", m_node_id);
  archive >> qtils::ArchiveProperty("pin", m_pin_id);
}

bool ConnectionSide::operator==(const ConnectionSide &other) const {
  return m_node_id == other.m_node_id && m_pin_id == other.m_pin_id;
}

bool ConnectionSide::operator!=(const ConnectionSide &other) const {
  return m_node_id != other.m_node_id || m_pin_id != other.m_pin_id;
}

/* --------------------------------- Connection ----------------------------- */

Connection::Connection() : m_parent(nullptr), m_visible(true) {}

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

void Connection::serialize(qtils::OArchive &archive) const {
  Object::serialize(archive);

  archive << qtils::ArchiveProperty("visible", m_visible);
  archive << qtils::ArchiveProperty("output", m_output_side);
  archive << qtils::ArchiveProperty("input", m_input_side);
}

void Connection::deserialize(qtils::IArchive &archive) {
  Object::deserialize(archive);

  archive >> qtils::ArchiveProperty("visible", m_visible);
  archive >> qtils::ArchiveProperty("output", m_output_side);
  archive >> qtils::ArchiveProperty("input", m_input_side);
}

void Connection::init(const Connection *connection) {
  Object::init(connection);

  m_visible = connection->m_visible;
  m_input_side = connection->m_input_side;
  m_output_side = connection->m_output_side;
}

void Connection::setParent(NodeLayer *parent) { m_parent = parent; }

}  // namespace flow_document
