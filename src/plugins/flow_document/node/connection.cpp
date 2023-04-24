/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Connection::Connection(Pin &out, Pin &in) : m_in(in), m_out(out) {
  out.addListener([this](auto &&data) {
    m_in.setData(std::forward<decltype(data)>(data));
  });
}

Connection::~Connection() = default;

const Pin &Connection::getPin(Pin::Type type) const {
  return type == Pin::Type::In ? m_in : m_out;
}

Pin &Connection::getPin(Pin::Type type) {
  return type == Pin::Type::In ? m_in : m_out;
}

}  // namespace flow_document
