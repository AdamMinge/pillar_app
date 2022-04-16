/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/node_factory_container.h"
#include "flow/modules/node/node_factory.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  NodeFactoryContainer::NodeFactoryContainer() = default;

  NodeFactoryContainer::~NodeFactoryContainer() = default;

  void
  NodeFactoryContainer::addFactory(std::unique_ptr<NodeFactory> node_factory)
  {
    m_factories.emplace_back(std::move(node_factory));
  }

  void NodeFactoryContainer::removeFactory(const NodeFactory &node_factory)
  {
    std::erase_if(m_factories, [&node_factory](auto &current_node_factory) {
      return current_node_factory.get() == std::addressof(node_factory);
    });
  }

  std::list<std::unique_ptr<NodeFactory>>::const_iterator
  NodeFactoryContainer::begin() const
  {
    return m_factories.begin();
  }

  std::list<std::unique_ptr<NodeFactory>>::const_iterator
  NodeFactoryContainer::end() const
  {
    return m_factories.end();
  }

  std::list<std::unique_ptr<NodeFactory>>::iterator
  NodeFactoryContainer::begin()
  {
    return m_factories.begin();
  }

  std::list<std::unique_ptr<NodeFactory>>::iterator NodeFactoryContainer::end()
  {
    return m_factories.end();
  }

  size_t NodeFactoryContainer::size() const { return m_factories.size(); }

}// namespace node
