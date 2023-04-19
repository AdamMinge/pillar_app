/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/node/node.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

Node::Node() = default;

Node::~Node() = default;

unsigned Node::getPinsCounts(Pin::Type type) const {
  return getPins(type).size();
}

const Pin &Node::getPin(Pin::Type type, unsigned index) const {
  auto &pins = getPins(type);
  Q_ASSERT(pins.size() > index);
  return *pins[index];
}

Pin &Node::getPin(Pin::Type type, unsigned index) {
  auto &pins = getPins(type);
  Q_ASSERT(pins.size() > index);
  return *pins[index];
}

void Node::insertPin(Pin::Type type, std::unique_ptr<Pin> pin, int index) {
  auto &pins = getPins(type);
  auto insert_iter = pins.insert(pins.begin() + index, std::move(pin));

  if (type == Pin::Type::In)
    (*insert_iter)->addListener([this](auto &&data) { this->compute(); });
}

void Node::removePin(Pin::Type type, int index) {
  auto &pins = getPins(type);
  pins.erase(pins.begin() + index);
}

std::vector<std::unique_ptr<Pin>> &Node::getPins(Pin::Type type) {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

const std::vector<std::unique_ptr<Pin>> &Node::getPins(Pin::Type type) const {
  return type == Pin::Type::Out ? m_out_pins : m_in_pins;
}

}  // namespace plugin::flow_document
