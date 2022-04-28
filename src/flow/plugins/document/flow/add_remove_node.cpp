/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/add_remove_node.h"
#include "flow/plugins/document/flow/flow_scene.h"
/* ----------------------------------- LibFlow ------------------------------ */
#include <flow/libflow/node/node.h>
#include <flow/libflow/node/node_factory.h>
#include <flow/libflow/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace
{
  flow::node::NodeFactory *getNodeFactory(const QString &node_to_create_id)
  {
    auto node_factories_list = flow::PluginManager::getInstance()
                                 .getObjects<flow::node::NodeFactories>();

    for (auto node_factories : node_factories_list)
      if (auto factory = node_factories->getFactory(node_to_create_id); factory)
        return factory;

    Q_ASSERT(false);
  }
};// namespace

/* ---------------------------- AddRemoveNodeCommand ------------------------ */

AddRemoveNodeCommand::AddRemoveNodeCommand(
  QString name, FlowScene *scene, flow::node::Node *node_to_remove,
  flow::command::Command *parent)
    : flow::command::Command(std::move(name), parent), m_scene(scene),
      m_node_to_remove(node_to_remove), m_node_factory()
{}

AddRemoveNodeCommand::AddRemoveNodeCommand(
  QString name, FlowScene *scene, const QString &node_to_create_id,
  flow::command::Command *parent)
    : flow::command::Command(std::move(name), parent), m_scene(scene),
      m_node_to_remove(nullptr),
      m_node_factory(getNodeFactory(node_to_create_id))
{}

AddRemoveNodeCommand::~AddRemoveNodeCommand() = default;

void AddRemoveNodeCommand::addNode()
{
  Q_ASSERT(!m_node_to_remove);
  m_node_to_remove = m_node_factory->create().release();
  m_scene->addItem(m_node_to_remove);
}

void AddRemoveNodeCommand::removeNode()
{
  Q_ASSERT(m_node_to_remove);
  m_scene->removeItem(m_node_to_remove);
  m_node_to_remove = nullptr;
}

/* ------------------------------ AddNodeCommand ---------------------------- */

AddNodeCommand::AddNodeCommand(
  FlowScene *scene, const QString &node_to_create_id, Command *parent)
    : AddRemoveNodeCommand(
        QLatin1String("AddNode"), scene, node_to_create_id, parent)
{
  setText(QObject::tr("Add Node"));
}

AddNodeCommand::~AddNodeCommand() = default;

void AddNodeCommand::redo() { addNode(); }

void AddNodeCommand::undo() { removeNode(); }

/* ----------------------------- RemoveNodeCommand -------------------------- */

RemoveNodeCommand::RemoveNodeCommand(
  FlowScene *scene, flow::node::Node *node_to_remove, Command *parent)
    : AddRemoveNodeCommand(
        QLatin1String("RemoveNode"), scene, node_to_remove, parent)
{
  setText(QObject::tr("Remove Node"));
}

RemoveNodeCommand::~RemoveNodeCommand() = default;

void RemoveNodeCommand::redo() { removeNode(); }

void RemoveNodeCommand::undo() { addNode(); }
