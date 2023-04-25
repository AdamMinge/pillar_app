#ifndef FLOW_DOCUMENT_FLOW_NODE_H
#define FLOW_DOCUMENT_FLOW_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/flow_object.h"
#include "flow_document/flow/flow_pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API FlowNode : public FlowObject {
 public:
  explicit FlowNode();
  ~FlowNode() override;

  [[nodiscard]] size_t getPinsCounts(FlowPin::Type type) const;

  [[nodiscard]] const FlowPin &getPin(FlowPin::Type type, size_t index) const;
  [[nodiscard]] FlowPin &getPin(FlowPin::Type type, size_t index);

  void insertPin(FlowPin::Type type, FlowPin pin, size_t index);
  void removePin(FlowPin::Type type, size_t index);

 protected:
  virtual void compute() = 0;

 private:
  [[nodiscard]] std::vector<FlowPin> &getPins(FlowPin::Type type);
  [[nodiscard]] const std::vector<FlowPin> &getPins(FlowPin::Type type) const;

 private:
  std::vector<FlowPin> m_out_pins;
  std::vector<FlowPin> m_in_pins;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_NODE_H
