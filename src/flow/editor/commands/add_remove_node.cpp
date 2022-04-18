/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/commands/add_remove_node.h"
#include "flow/editor/document/flow/flow_scene.h"
/* -------------------------------------------------------------------------- */

/* ---------------------------- AddRemoveNodeCommand ------------------------ */

AddRemoveNodeCommand::AddRemoveNodeCommand(
  FlowScene *scene, node::Node *node_to_remove, Type type, Command *parent)
    : Command(type, parent), m_scene(scene), m_node_to_remove(node_to_remove),
      m_node_to_create_id()
{}

AddRemoveNodeCommand::AddRemoveNodeCommand(
  FlowScene *scene, QString node_to_create_id, Type type, Command *parent)
    : Command(type, parent), m_scene(scene), m_node_to_remove(nullptr),
      m_node_to_create_id(std::move(node_to_create_id))
{}

AddRemoveNodeCommand::~AddRemoveNodeCommand() = default;

void AddRemoveNodeCommand::addNode()
{
  Q_ASSERT(!m_node_to_remove);
  //m_scene->addItem()
}

void AddRemoveNodeCommand::removeNode()
{
  Q_ASSERT(m_node_to_remove);
  m_scene->removeItem(m_node_to_remove);
  m_node_to_remove = nullptr;
}

/* ------------------------------ AddNodeCommand ---------------------------- */

AddNodeCommand::AddNodeCommand(
  FlowScene *scene, QString node_to_create_id, Command *parent)
    : AddRemoveNodeCommand(
        scene, std::move(node_to_create_id), Type::AddNode, parent)
{
  setText(QObject::tr("Add Node"));
}

AddNodeCommand::~AddNodeCommand() = default;

void AddNodeCommand::redo() { addNode(); }

void AddNodeCommand::undo() { removeNode(); }

/* ----------------------------- RemoveNodeCommand -------------------------- */

RemoveNodeCommand::RemoveNodeCommand(
  FlowScene *scene, node::Node *node_to_remove, Command *parent)
    : AddRemoveNodeCommand(scene, node_to_remove, Type::RemoveNode, parent)
{
  setText(QObject::tr("Remove Node"));
}

RemoveNodeCommand::~RemoveNodeCommand() = default;

void RemoveNodeCommand::redo() { removeNode(); }

void RemoveNodeCommand::undo() { addNode(); }
