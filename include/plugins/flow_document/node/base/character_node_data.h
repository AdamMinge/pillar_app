#ifndef FLOW_CHARACTER_NODE_DATA_H
#define FLOW_CHARACTER_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QChar>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API CharacterNodeData : public NodeData {
 public:
  explicit CharacterNodeData(QChar value);
  ~CharacterNodeData() override;

  void setValue(QChar value);
  [[nodiscard]] QChar getValue() const;

  void assign(const NodeData &data) override;

 private:
  QChar m_value;
};

}  // namespace flow_document

#endif  // FLOW_CHARACTER_NODE_DATA_H
