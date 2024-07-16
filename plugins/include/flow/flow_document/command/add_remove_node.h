#ifndef FLOW_DOCUMENT_ADD_REMOVE_NODE_H
#define FLOW_DOCUMENT_ADD_REMOVE_NODE_H

/* ---------------------------------- Standard ------------------------------ */
#include <list>
#include <memory>
/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class NodeLayer;
class Node;

/* --------------------------------- NodeEntry ------------------------------ */

struct FLOW_DOCUMENT_API NodeEntry {
 public:
  explicit NodeEntry(NodeEntry&& other);
  explicit NodeEntry(NodeLayer* node_layer, qsizetype index);
  explicit NodeEntry(NodeLayer* node_layer, std::unique_ptr<Node> new_node,
                     qsizetype index);
  ~NodeEntry();

 public:
  NodeLayer* node_layer;
  std::unique_ptr<Node> new_node;
  qsizetype index;
};

/* ------------------------------ AddRemoveNodes ---------------------------- */

class FLOW_DOCUMENT_API AddRemoveNodes : public pillar::Command {
 public:
  explicit AddRemoveNodes(const QString& name, FlowDocument* document,
                          std::list<NodeEntry> entries,
                          Command* parent = nullptr);
  ~AddRemoveNodes() override;

 protected:
  void addNode();
  void removeNode();

 protected:
  FlowDocument* m_document;
  std::list<NodeEntry> m_entries;
};

/* ---------------------------------- AddNodes ------------------------------ */

class FLOW_DOCUMENT_API AddNodes : public AddRemoveNodes {
 public:
  explicit AddNodes(FlowDocument* document, std::list<NodeEntry> entries,
                    Command* parent = nullptr);
  ~AddNodes() override;

  void undo() override;
  void redo() override;
};

/* -------------------------------- RemoveNodes ----------------------------- */

class FLOW_DOCUMENT_API RemoveNodes : public AddRemoveNodes {
 public:
  RemoveNodes(FlowDocument* document, std::list<NodeEntry> entries,
              Command* parent = nullptr);
  ~RemoveNodes() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_ADD_REMOVE_NODE_H