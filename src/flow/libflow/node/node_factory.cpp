/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/node_factory.h"
#include "flow/libflow/node/node.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  /* ------------------------------- NodeFactory ---------------------------- */

  NodeFactory::NodeFactory(QString name) : m_name(std::move(name)) {}

  NodeFactory::~NodeFactory() = default;

  QString NodeFactory::getName() const { return m_name; }

  /* ------------------------------ NodeFactories --------------------------- */

  NodeFactories::NodeFactories(QString name) : m_name(std::move(name)) {}

  NodeFactories::~NodeFactories() = default;

  void NodeFactories::registerFactory(
    QString node_id, std::unique_ptr<NodeFactory> factory)
  {
    Q_ASSERT(!m_factories.contains(node_id));
    m_factories.insert(std::make_pair(std::move(node_id), std::move(factory)));
  }

  void NodeFactories::unregisterFactory(const QString &node_id)
  {
    Q_ASSERT(m_factories.contains(node_id));
    m_factories.erase(node_id);
  }

  QStringList NodeFactories::getNodeIds() const
  {
    QStringList keys;
    for (const auto &[key, _] : m_factories) keys << key;

    return keys;
  }

  NodeFactory *NodeFactories::getFactory(const QString &node_id) const
  {
    if (!m_factories.contains(node_id)) return nullptr;
    return m_factories.at(node_id).get();
  }

  std::unique_ptr<Node> NodeFactories::create(const QString &node_id) const
  {
    if (!m_factories.contains(node_id)) return nullptr;
    return m_factories.at(node_id)->create();
  }

  QString NodeFactories::getName() const { return m_name; }

}// namespace flow::node