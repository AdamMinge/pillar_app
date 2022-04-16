/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory_container.h"
#include "flow/modules/node/converter/converter_factory.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  ConverterFactoryContainer::ConverterFactoryContainer(QObject *parent)
      : QObject(parent)
  {}

  ConverterFactoryContainer::~ConverterFactoryContainer() = default;

  void ConverterFactoryContainer::addFactory(
    std::unique_ptr<ConverterFactory> node_factory)
  {
    m_factories.emplace_back(std::move(node_factory));
  }

  void
  ConverterFactoryContainer::removeFactory(const ConverterFactory &node_factory)
  {
    std::erase_if(m_factories, [&node_factory](auto &current_node_factory) {
      return current_node_factory.get() == std::addressof(node_factory);
    });
  }

  std::list<std::unique_ptr<ConverterFactory>>::const_iterator
  ConverterFactoryContainer::begin() const
  {
    return m_factories.begin();
  }

  std::list<std::unique_ptr<ConverterFactory>>::const_iterator
  ConverterFactoryContainer::end() const
  {
    return m_factories.end();
  }

  std::list<std::unique_ptr<ConverterFactory>>::iterator
  ConverterFactoryContainer::begin()
  {
    return m_factories.begin();
  }

  std::list<std::unique_ptr<ConverterFactory>>::iterator
  ConverterFactoryContainer::end()
  {
    return m_factories.end();
  }

  size_t ConverterFactoryContainer::size() const { return m_factories.size(); }

}// namespace node::converter
