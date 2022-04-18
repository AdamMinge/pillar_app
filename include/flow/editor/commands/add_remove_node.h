#ifndef FLOW_ADD_REMOVE_NODE_H
#define FLOW_ADD_REMOVE_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/commands/command.h"
/* -------------------------------------------------------------------------- */

namespace node
{
  class Node;
}

class FlowScene;

class AddRemoveNodeCommand : public Command
{
public:
  explicit AddRemoveNodeCommand(
    FlowScene *scene, node::Node *node_to_remove, Type type,
    Command *parent = nullptr);
  explicit AddRemoveNodeCommand(
    FlowScene *scene, QString node_to_create_id, Type type,
    Command *parent = nullptr);
  ~AddRemoveNodeCommand() override;

protected:
  void addNode();
  void removeNode();

private:
  FlowScene *m_scene;
  node::Node *m_node_to_remove;
  QString m_node_to_create_id;
};

class AddNodeCommand : public AddRemoveNodeCommand
{
public:
  explicit AddNodeCommand(
    FlowScene *scene, QString node_to_create_id, Command *parent = nullptr);
  ~AddNodeCommand() override;

  void redo() override;
  void undo() override;
};

class RemoveNodeCommand : public AddRemoveNodeCommand
{
public:
  explicit RemoveNodeCommand(
    FlowScene *scene, node::Node *node_to_remove, Command *parent = nullptr);
  ~RemoveNodeCommand() override;

  void redo() override;
  void undo() override;
};

#endif//FLOW_ADD_REMOVE_NODE_H
