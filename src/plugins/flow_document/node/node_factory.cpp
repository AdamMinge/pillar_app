/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/node_factory.h"

#include "flow_document/node/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- NodeFactory ---------------------------- */

NodeFactory::NodeFactory(QString name, QString node_type)
    : m_name(std::move(name)), m_node_type(std::move(node_type)) {}

NodeFactory::~NodeFactory() = default;

QString NodeFactory::getName() const { return m_name; }

QString NodeFactory::getNodeType() const { return m_node_type; }

/* ------------------------------ NodeFactories --------------------------- */

NodeFactories::NodeFactories(QString name) : m_name(std::move(name)) {}

NodeFactories::~NodeFactories() = default;

void NodeFactories::registerFactory(std::unique_ptr<NodeFactory> factory) {
  Q_ASSERT(!m_factories.contains(factory->getNodeType()));
  m_factories.insert(
      std::make_pair(std::move(factory->getNodeType()), std::move(factory)));
}

void NodeFactories::unregisterFactory(const QString &node_type) {
  Q_ASSERT(m_factories.contains(node_type));
  m_factories.erase(node_type);
}

QStringList NodeFactories::getNodeTypes() const {
  QStringList keys;
  for (const auto &[key, _] : m_factories) keys << key;

  return keys;
}

NodeFactory *NodeFactories::getFactory(const QString &node_type) const {
  if (!m_factories.contains(node_type)) return nullptr;
  return m_factories.at(node_type).get();
}

std::unique_ptr<Node> NodeFactories::create(const QString &node_type) const {
  if (!m_factories.contains(node_type)) return nullptr;
  return m_factories.at(node_type)->create();
}

QString NodeFactories::getName() const { return m_name; }

}  // namespace flow_document