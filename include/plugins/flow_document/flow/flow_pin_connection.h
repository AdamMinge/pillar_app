#ifndef FLOW_DOCUMENT_FLOW_PIN_CONNECTION_H
#define FLOW_DOCUMENT_FLOW_PIN_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/flow_pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API FlowPinConnection {
 public:
  explicit FlowPinConnection(FlowPin &out, FlowPin &in);
  ~FlowPinConnection();

  [[nodiscard]] const FlowPin &getFlowPin(FlowPin::Type type) const;
  [[nodiscard]] FlowPin &getFlowPin(FlowPin::Type type);

 private:
  FlowPin &m_in;
  FlowPin &m_out;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_PIN_CONNECTION_H
