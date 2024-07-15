#ifndef FLOW_DOCUMENT_DUPLICATE_NODE_H
#define FLOW_DOCUMENT_DUPLICATE_NODE_H

/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class NodeLayer;
class Node;

/* ----------------------------- DuplicateNodeData -------------------------- */

struct DuplicateNodeData {
 public:
  explicit DuplicateNodeData(DuplicateNodeData&& other);
  explicit DuplicateNodeData(Node* node);
  ~DuplicateNodeData();

 public:
  NodeLayer* node_layer;
  std::unique_ptr<Node> copy_node;
  qsizetype index;
};

/* ------------------------------ DuplicateNodes ---------------------------- */

class FLOW_DOCUMENT_API DuplicateNodes : public egnite::Command {
 public:
  explicit DuplicateNodes(FlowDocument* document, QList<Node*> nodes,
                          Command* parent = nullptr);
  ~DuplicateNodes() override;

  void undo() override;
  void redo() override;

 protected:
  FlowDocument* m_document;
  std::list<DuplicateNodeData> m_duplicate_data;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_DUPLICATE_NODE_H