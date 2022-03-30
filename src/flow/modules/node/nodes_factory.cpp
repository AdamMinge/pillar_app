/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/nodes_factory.h"
#include "flow/modules/node/node.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  NodesFactory::NodesFactory() = default;

  NodesFactory::~NodesFactory() = default;

  std::unique_ptr<Node> NodesFactory::createNode(const QString &id) const
  {
    if (!m_factories.contains(id)) return nullptr;
    return m_factories[id]();
  }

  QStringList NodesFactory::getAvailableNodes() const
  {
    return m_factories.keys();
  }

  void NodesFactory::registerFactory(const QString &id, const Factory &factory)
  {
    m_factories.insert(id, factory);
  }

  void NodesFactory::unregisterFactory(const QString &id)
  {
    m_factories.remove(id);
  }

}// namespace node
