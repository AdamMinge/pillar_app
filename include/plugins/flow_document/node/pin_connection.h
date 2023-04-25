#ifndef FLOW_DOCUMENT_NODE_CONNECTION_H
#define FLOW_DOCUMENT_NODE_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API PinConnection {
 public:
  explicit PinConnection(Pin &out, Pin &in);
  ~PinConnection();

  [[nodiscard]] const Pin &getPin(Pin::Type type) const;
  [[nodiscard]] Pin &getPin(Pin::Type type);

 private:
  Pin &m_in;
  Pin &m_out;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_CONNECTION_H
