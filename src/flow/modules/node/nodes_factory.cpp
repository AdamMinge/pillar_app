/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/nodes_factory.h"
#include "flow/modules/node/node.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  /* -------------------------------- NodesFactory ---------------------------- */

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

  /* ---------------------------------- Factory ------------------------------- */

  NodesFactory::Factory::Factory() : Factory({}, {}, {}) {}

  NodesFactory::Factory::Factory(Creator creator, QString name, QIcon icon)
      : m_creator(std::move(creator)), m_icon(std::move(icon)),
        m_name(std::move(name))
  {}

  NodesFactory::Factory::~Factory() = default;

  const NodesFactory::Factory::Creator &
  NodesFactory::Factory::getCreator() const
  {
    return m_creator;
  }

  const QString &NodesFactory::Factory::getName() const { return m_name; }

  const QIcon &NodesFactory::Factory::getIcon() const { return m_icon; }

  std::unique_ptr<Node> NodesFactory::Factory::operator()() const
  {
    return m_creator();
  }

}// namespace node
