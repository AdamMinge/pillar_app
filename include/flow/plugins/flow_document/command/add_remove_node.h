#ifndef FLOW_ADD_REMOVE_NODE_H
#define FLOW_ADD_REMOVE_NODE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class Node;
class NodeFactory;

class FlowDocument;

class FLOW_DOCUMENT_API AddRemoveNodeCommand : public flow::Command {
 public:
  explicit AddRemoveNodeCommand(QString name, FlowDocument *document,
                                Node *node_to_remove,
                                flow::Command *parent = nullptr);
  explicit AddRemoveNodeCommand(QString name, FlowDocument *document,
                                const QString &node_to_create_id,
                                const QPointF &pos,
                                flow::Command *parent = nullptr);
  ~AddRemoveNodeCommand() override;

 protected:
  void addNode();
  void removeNode();

 private:
  FlowDocument *m_document;
  Node *m_node_to_remove;
  Node *m_node_to_add;
};

class AddNodeCommand : public AddRemoveNodeCommand {
 public:
  explicit AddNodeCommand(FlowDocument *document,
                          const QString &node_to_create_id, const QPointF &pos,
                          flow::Command *parent = nullptr);
  ~AddNodeCommand() override;

  void redo() override;
  void undo() override;
};

class RemoveNodeCommand : public AddRemoveNodeCommand {
 public:
  explicit RemoveNodeCommand(FlowDocument *document, Node *node_to_remove,
                             flow::Command *parent = nullptr);
  ~RemoveNodeCommand() override;

  void redo() override;
  void undo() override;
};

}  // namespace plugin::flow_document

#endif  // FLOW_ADD_REMOVE_NODE_H
