#ifndef FLOW_STRING_NODE_DATA_H
#define FLOW_STRING_NODE_DATA_H

/* ------------------------------------- Qt --------------------------------- */
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
#include "flow/plugins/flow_document/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class FLOW_DOCUMENT_API StringNodeData : public NodeData {
 public:
  explicit StringNodeData(QString value);
  ~StringNodeData() override;

  void setValue(QString value);
  [[nodiscard]] QString getValue() const;

  void assign(const NodeData &data) override;

 private:
  QString m_value;
};

}  // namespace plugin::flow_document

#endif  // FLOW_STRING_NODE_DATA_H
