#ifndef FLOW_INTEGER_NODE_DATA_H
#define FLOW_INTEGER_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API IntegerNodeData : public NodeData {
 public:
  explicit IntegerNodeData(int value);
  ~IntegerNodeData() override;

  void setValue(int value);
  [[nodiscard]] int getValue() const;

  void assign(const NodeData &data) override;

 private:
  int m_value;
};

}  // namespace flow_document

#endif  // FLOW_INTEGER_NODE_DATA_H
