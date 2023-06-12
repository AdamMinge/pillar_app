/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/node.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

Node::Node() : Object(Type::Node), m_visible(true) {}

Node::~Node() = default;

void Node::setVisible(bool visible) { m_visible = visible; }

bool Node::isVisible() const { return m_visible; }

void Node::setPosition(const QPointF &position) { m_position = position; }

QPointF Node::getPosition() const { return m_position; }

size_t Node::getPinsCounts(Pin::Type type) const {
  return getPins(type).size();
}

const Pin &Node::getPin(Pin::Type type, size_t index) const {
  auto &pins = getPins(type);
  Q_ASSERT(pins.size() > index);
  return pins[index];
}

Pin &Node::getPin(Pin::Type type, size_t index) {
  auto &pins = getPins(type);
  Q_ASSERT(pins.size() > index);
  return pins[index];
}

void Node::insertPin(Pin::Type type, Pin pin, size_t index) {
  auto &pins = getPins(type);
  auto insert_iter = pins.insert(pins.begin() + index, std::move(pin));

  if (type == Pin::Type::In)
    (*insert_iter).addListener([this](auto &&data) { this->compute(); });
}

void Node::removePin(Pin::Type type, size_t index) {
  auto &pins = getPins(type);
  pins.erase(pins.begin() + index);
}

NodeLayer *Node::getParent() const { return m_parent; }

void Node::serialize(utils::OArchive &archive) const {
  Object::serialize(archive);

  archive << utils::ArchiveProperty("position", m_position);
  archive << utils::ArchiveProperty("visible", m_visible);
}

void Node::deserialize(utils::IArchive &archive) {
  Object::deserialize(archive);
}

void Node::setParent(NodeLayer *parent) { m_parent = parent; }

void Node::init(const Node *node) {
  Object::init(node);

  m_position = node->m_position;
  m_out_pins = node->m_out_pins;
  m_in_pins = node->m_in_pins;
}

QVector<Pin> &Node::getPins(Pin::Type type) {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

const QVector<Pin> &Node::getPins(Pin::Type type) const {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

}  // namespace flow_document
