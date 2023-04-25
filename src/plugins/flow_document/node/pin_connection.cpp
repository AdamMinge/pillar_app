/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/pin_connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

PinConnection::PinConnection(Pin &out, Pin &in) : m_in(in), m_out(out) {
  out.addListener([this](auto &&data) {
    m_in.setData(std::forward<decltype(data)>(data));
  });
}

PinConnection::~PinConnection() = default;

const Pin &PinConnection::getPin(Pin::Type type) const {
  return type == Pin::Type::In ? m_in : m_out;
}

Pin &PinConnection::getPin(Pin::Type type) {
  return type == Pin::Type::In ? m_in : m_out;
}

}  // namespace flow_document
