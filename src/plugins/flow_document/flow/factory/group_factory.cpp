/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/group_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

GroupFactory::GroupFactory(QString name)
    : Factory(Type::GroupFactory, std::move(name)) {}

GroupFactory::~GroupFactory() = default;

void GroupFactory::append(std::unique_ptr<Factory> factory) {
  insert(m_factories.size(), std::move(factory));
}

void GroupFactory::insert(qsizetype index, std::unique_ptr<Factory> factory) {
  auto insert_iter = m_factories.begin() + index;
  auto added_factory_iter = m_factories.insert(insert_iter, std::move(factory));

  (*added_factory_iter)->setParent(this);
}

void GroupFactory::remove(qsizetype index) { Q_UNUSED(take(index)); }

std::unique_ptr<Factory> GroupFactory::take(qsizetype index) {
  auto take_iter = m_factories.begin() + index;
  auto factory = std::move(*take_iter);
  m_factories.erase(take_iter);

  factory->setParent(nullptr);
  return factory;
}

Factory* GroupFactory::at(qsizetype index) const {
  return m_factories.at(index).get();
}

qsizetype GroupFactory::indexOf(Factory* factory) const {
  auto iter = std::find_if(m_factories.cbegin(), m_factories.cend(),
                           [factory](const auto& factory_ptr) {
                             return factory_ptr.get() == factory;
                           });

  if (iter != m_factories.end())
    return std::distance(m_factories.begin(), iter);

  return -1;
}

qsizetype GroupFactory::size() const { return m_factories.size(); }

GroupFactory::Factories::iterator GroupFactory::begin() {
  return m_factories.begin();
}

GroupFactory::Factories::iterator GroupFactory::end() {
  return m_factories.end();
}

GroupFactory::Factories::const_iterator GroupFactory::begin() const {
  return m_factories.begin();
}

GroupFactory::Factories::const_iterator GroupFactory::end() const {
  return m_factories.end();
}

}  // namespace flow_document