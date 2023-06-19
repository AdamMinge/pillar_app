/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Factory::Factory(Type type, QString name, QString section, QIcon icon,
                 QObject* parent)
    : QObject(parent),
      m_type(type),
      m_name(std::move(name)),
      m_section(std::move(section)),
      m_icon(std::move(icon)) {}

Factory::~Factory() = default;

Factory::Type Factory::getType() const { return m_type; }

QString Factory::getName() const { return m_name; }

QString Factory::getSection() const { return m_section; }

QIcon Factory::getIcon() const { return m_icon; }

}  // namespace flow_document