#ifndef FLOW_BOOLEAN_NODE_DATA_H
#define FLOW_BOOLEAN_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API BooleanNodeData : public NodeData {
 public:
  explicit BooleanNodeData(bool value);
  ~BooleanNodeData() override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

  void assign(const NodeData &data) override;

 private:
  bool m_value;
};

}  // namespace flow_document

#endif  // FLOW_BOOLEAN_NODE_DATA_H
