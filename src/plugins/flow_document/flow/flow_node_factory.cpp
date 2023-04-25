/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow_node_factory.h"

#include "flow_document/flow/flow_node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ FlowNodeFactory --------------------------- */

FlowNodeFactory::FlowNodeFactory(QString name, QString node_type)
    : m_name(std::move(name)), m_node_type(std::move(node_type)) {}

FlowNodeFactory::~FlowNodeFactory() = default;

QString FlowNodeFactory::getName() const { return m_name; }

QString FlowNodeFactory::getNodeType() const { return m_node_type; }

/* ----------------------------- FlowNodeFactories -------------------------- */

FlowNodeFactories::FlowNodeFactories(QString name) : m_name(std::move(name)) {}

FlowNodeFactories::~FlowNodeFactories() = default;

void FlowNodeFactories::registerFactory(
    std::unique_ptr<FlowNodeFactory> factory) {
  Q_ASSERT(!m_factories.contains(factory->getNodeType()));
  m_factories.insert(
      std::make_pair(std::move(factory->getNodeType()), std::move(factory)));
}

void FlowNodeFactories::unregisterFactory(const QString &node_type) {
  Q_ASSERT(m_factories.contains(node_type));
  m_factories.erase(node_type);
}

QStringList FlowNodeFactories::getNodeTypes() const {
  QStringList keys;
  for (const auto &[key, _] : m_factories) keys << key;

  return keys;
}

FlowNodeFactory *FlowNodeFactories::getFactory(const QString &node_type) const {
  if (!m_factories.contains(node_type)) return nullptr;
  return m_factories.at(node_type).get();
}

std::unique_ptr<FlowNode> FlowNodeFactories::create(
    const QString &node_type) const {
  if (!m_factories.contains(node_type)) return nullptr;
  return m_factories.at(node_type)->create();
}

QString FlowNodeFactories::getName() const { return m_name; }

}  // namespace flow_document