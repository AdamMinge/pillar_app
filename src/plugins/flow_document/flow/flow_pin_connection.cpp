/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow_pin_connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowPinConnection::FlowPinConnection(FlowPin &out, FlowPin &in)
    : m_in(in), m_out(out) {
  out.addListener([this](auto &&data) {
    m_in.setData(std::forward<decltype(data)>(data));
  });
}

FlowPinConnection::~FlowPinConnection() = default;

const FlowPin &FlowPinConnection::getFlowPin(FlowPin::Type type) const {
  return type == FlowPin::Type::In ? m_in : m_out;
}

FlowPin &FlowPinConnection::getFlowPin(FlowPin::Type type) {
  return type == FlowPin::Type::In ? m_in : m_out;
}

}  // namespace flow_document
