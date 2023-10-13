/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/node.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Node --------------------------------- */

Node::Node() : m_parent(nullptr), m_visible(true) {}

Node::~Node() = default;

void Node::setVisible(bool visible) { m_visible = visible; }

bool Node::isVisible() const { return m_visible; }

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
    (*insert_iter).addListener(index, [this](auto &&data) { this->compute(); });
}

void Node::removePin(Pin::Type type, size_t index) {
  auto &pins = getPins(type);
  pins.erase(pins.begin() + index);
}

QWidget *Node::getEmbeddedWidget() const { return nullptr; }

NodeLayer *Node::getParent() const { return m_parent; }

void Node::serialize(utils::OArchive &archive) const {
  MoveableObject::serialize(archive);

  archive << utils::ArchiveProperty("visible", m_visible);
}

void Node::deserialize(utils::IArchive &archive) {
  MoveableObject::deserialize(archive);

  archive >> utils::ArchiveProperty("visible", m_visible);
}

void Node::setParent(NodeLayer *parent) { m_parent = parent; }

void Node::init(const Node *node) {
  MoveableObject::init(node);

  m_visible = node->m_visible;
}

QVector<Pin> &Node::getPins(Pin::Type type) {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

const QVector<Pin> &Node::getPins(Pin::Type type) const {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

/* ----------------------------- NodeWithOneParam --------------------------- */

NodeWithOneParam::NodeWithOneParam() {
  auto in_pin = Pin({}, "A");
  auto out_pin = Pin({}, "Q");

  insertPin(Pin::Type::In, std::move(in_pin), 0);
  insertPin(Pin::Type::Out, std::move(out_pin), 0);
}

NodeWithOneParam::~NodeWithOneParam() = default;

/* ---------------------------- NodeWithTwoParams --------------------------- */

NodeWithTwoParams::NodeWithTwoParams() {
  auto in_pin = Pin({}, "B");

  insertPin(Pin::Type::In, std::move(in_pin), 1);
}

NodeWithTwoParams::~NodeWithTwoParams() = default;

/* ----------------------------- NodeWithThreeParams ------------------------ */

NodeWithThreeParams::NodeWithThreeParams() {
  auto in_pin = Pin({}, "C");

  insertPin(Pin::Type::In, std::move(in_pin), 2);
}

NodeWithThreeParams::~NodeWithThreeParams() = default;

}  // namespace flow_document
