#ifndef FLOW_DOCUMENT_RAISE_LOWER_NODE_H
#define FLOW_DOCUMENT_RAISE_LOWER_NODE_H

/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class NodeLayer;
class Node;

/* ----------------------------- RaiseLowerNodes ---------------------------- */

class FLOW_DOCUMENT_API RaiseLowerNodes : public pillar::Command {
 public:
  explicit RaiseLowerNodes(const QString& name, FlowDocument* document,
                           QList<Node*> nodes, Command* parent = nullptr);
  ~RaiseLowerNodes() override;

 protected:
  void raiseNodes();
  void lowerNodes();

 private:
  void moveNodes(bool raise);
  void moveNode(Node* node, NodeLayer* parent, qsizetype index);

 protected:
  FlowDocument* m_document;
  QList<Node*> m_nodes;
};

/* -------------------------------- RaiseNodes ------------------------------ */

class FLOW_DOCUMENT_API RaiseNodes : public RaiseLowerNodes {
 public:
  explicit RaiseNodes(FlowDocument* document, QList<Node*> nodes,
                      Command* parent = nullptr);
  ~RaiseNodes() override;

  void undo() override;
  void redo() override;
};

/* -------------------------------- LowerNodes ------------------------------ */

class FLOW_DOCUMENT_API LowerNodes : public RaiseLowerNodes {
 public:
  explicit LowerNodes(FlowDocument* document, QList<Node*> nodes,
                      Command* parent = nullptr);
  ~LowerNodes() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_RAISE_LOWER_NODE_H
