#ifndef FLOW_NODE_DATA_H
#define FLOW_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API NodeData {
 public:
  explicit NodeData() = default;
  virtual ~NodeData() = default;

  virtual void assign(const NodeData &data) = 0;
};

}  // namespace flow_document

#endif  // FLOW_NODE_DATA_H
