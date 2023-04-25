/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow_node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowNode::FlowNode() = default;

FlowNode::~FlowNode() = default;

size_t FlowNode::getPinsCounts(FlowPin::Type type) const {
  return getPins(type).size();
}

const FlowPin &FlowNode::getPin(FlowPin::Type type, size_t index) const {
  auto &pins = getPins(type);
  Q_ASSERT(pins.size() > index);
  return pins[index];
}

FlowPin &FlowNode::getPin(FlowPin::Type type, size_t index) {
  auto &pins = getPins(type);
  Q_ASSERT(pins.size() > index);
  return pins[index];
}

void FlowNode::insertPin(FlowPin::Type type, FlowPin pin, size_t index) {
  auto &pins = getPins(type);
  auto insert_iter = pins.insert(pins.begin() + index, std::move(pin));

  if (type == FlowPin::Type::In)
    (*insert_iter).addListener([this](auto &&data) { this->compute(); });
}

void FlowNode::removePin(FlowPin::Type type, size_t index) {
  auto &pins = getPins(type);
  pins.erase(pins.begin() + index);
}

std::vector<FlowPin> &FlowNode::getPins(FlowPin::Type type) {
  return type == FlowPin::Type::Out ? m_out_pins : m_in_pins;
}

const std::vector<FlowPin> &FlowNode::getPins(FlowPin::Type type) const {
  return type == FlowPin::Type::Out ? m_out_pins : m_in_pins;
}

}  // namespace flow_document
