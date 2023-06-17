/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Factory::Factory(Type type, QString name)
    : m_type(type), m_name(std::move(name)), m_parent(nullptr) {}

Factory::~Factory() = default;

Factory::Type Factory::getType() const { return m_type; }

QString Factory::getName() const { return m_name; }

GroupFactory *Factory::getParent() const { return m_parent; }

void Factory::setParent(GroupFactory *parent) { m_parent = parent; }

}  // namespace flow_document