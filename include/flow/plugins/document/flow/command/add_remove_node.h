#ifndef FLOW_ADD_REMOVE_NODE_H
#define FLOW_ADD_REMOVE_NODE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/command/command.h"
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
  class NodeFactory;
}// namespace flow::node

class FlowDocument;

class FLOW_DOCUMENT_API AddRemoveNodeCommand : public flow::command::Command
{
public:
  explicit AddRemoveNodeCommand(
    QString name, FlowDocument *document, flow::node::Node *node_to_remove,
    flow::command::Command *parent = nullptr);
  explicit AddRemoveNodeCommand(
    QString name, FlowDocument *document, const QString &node_to_create_id,
    const QPointF &pos, flow::command::Command *parent = nullptr);
  ~AddRemoveNodeCommand() override;

protected:
  void addNode();
  void removeNode();

private:
  FlowDocument *m_document;
  flow::node::Node *m_node_to_remove;
  flow::node::NodeFactory *m_node_factory;
  QPointF m_pos;
};

class AddNodeCommand : public AddRemoveNodeCommand
{
public:
  explicit AddNodeCommand(
    FlowDocument *document, const QString &node_to_create_id,
    const QPointF &pos, flow::command::Command *parent = nullptr);
  ~AddNodeCommand() override;

  void redo() override;
  void undo() override;
};

class RemoveNodeCommand : public AddRemoveNodeCommand
{
public:
  explicit RemoveNodeCommand(
    FlowDocument *document, flow::node::Node *node_to_remove,
    flow::command::Command *parent = nullptr);
  ~RemoveNodeCommand() override;

  void redo() override;
  void undo() override;
};

#endif//FLOW_ADD_REMOVE_NODE_H
