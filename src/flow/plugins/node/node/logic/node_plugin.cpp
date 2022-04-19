/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/node_plugin.h"
#include "flow/plugins/node/node/logic/logic_node_and.h"
#include "flow/plugins/node/node/logic/logic_node_not.h"
#include "flow/plugins/node/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

NodePlugin::NodePlugin()
    : m_not_node(new LogicNodeNot), m_and_node(new LogicNodeAnd),
      m_or_node(new LogicNodeOr)
{
  addObject(m_not_node.get());
  addObject(m_and_node.get());
  addObject(m_or_node.get());
}

NodePlugin::~NodePlugin() = default;