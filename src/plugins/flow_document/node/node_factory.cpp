/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/node_factory.h"

#include "flow_document/node/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- NodeFactory ---------------------------- */

NodeFactory::NodeFactory(QString name, QString node_id)
    : m_name(std::move(name)), m_node_id(std::move(node_id)) {}

NodeFactory::~NodeFactory() = default;

QString NodeFactory::getName() const { return m_name; }

QString NodeFactory::getNodeId() const { return m_node_id; }

/* ------------------------------ NodeFactories --------------------------- */

NodeFactories::NodeFactories(QString name) : m_name(std::move(name)) {}

NodeFactories::~NodeFactories() = default;

void NodeFactories::registerFactory(std::unique_ptr<NodeFactory> factory) {
  Q_ASSERT(!m_factories.contains(factory->getNodeId()));
  m_factories.insert(
      std::make_pair(std::move(factory->getNodeId()), std::move(factory)));
}

void NodeFactories::unregisterFactory(const QString &node_id) {
  Q_ASSERT(m_factories.contains(node_id));
  m_factories.erase(node_id);
}

QStringList NodeFactories::getNodeIds() const {
  QStringList keys;
  for (const auto &[key, _] : m_factories) keys << key;

  return keys;
}

NodeFactory *NodeFactories::getFactory(const QString &node_id) const {
  if (!m_factories.contains(node_id)) return nullptr;
  return m_factories.at(node_id).get();
}

std::unique_ptr<Node> NodeFactories::create(const QString &node_id) const {
  if (!m_factories.contains(node_id)) return nullptr;
  return m_factories.at(node_id)->create();
}

QString NodeFactories::getName() const { return m_name; }

}  // namespace flow_document