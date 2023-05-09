/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Node::Node() = default;

Node::~Node() = default;

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

QVector<Pin> &Node::getPins(Pin::Type type) {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

const QVector<Pin> &Node::getPins(Pin::Type type) const {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

}  // namespace flow_document
