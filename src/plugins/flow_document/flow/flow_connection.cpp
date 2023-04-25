/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow_connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowConnection::FlowConnection(FlowPin &out, FlowPin &in)
    : m_in(in), m_out(out) {
  out.addListener([this](auto &&data) {
    m_in.setData(std::forward<decltype(data)>(data));
  });
}

FlowConnection::~FlowConnection() = default;

const FlowPin &FlowConnection::getPin(FlowPin::Type type) const {
  return type == FlowPin::Type::In ? m_in : m_out;
}

FlowPin &FlowConnection::getPin(FlowPin::Type type) {
  return type == FlowPin::Type::In ? m_in : m_out;
}

}  // namespace flow_document
