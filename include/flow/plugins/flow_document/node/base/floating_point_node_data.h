#ifndef FLOW_FLOATING_POINT_NODE_DATA_H
#define FLOW_FLOATING_POINT_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
#include "flow/plugins/flow_document/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class FLOW_DOCUMENT_API FloatingPointNodeData : public NodeData {
 public:
  explicit FloatingPointNodeData(double value);
  ~FloatingPointNodeData() override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

  void assign(const NodeData &data) override;

 private:
  double m_value;
};

}  // namespace plugin::flow_document

#endif  // FLOW_FLOATING_POINT_NODE_DATA_H
