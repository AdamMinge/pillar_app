/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/object_factory.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- ObjectFactory ---------------------------- */

ObjectFactory::ObjectFactory(Type type, QString name, QString section,
                             QIcon icon, QObject* parent)
    : QObject(parent),
      m_type(type),
      m_name(std::move(name)),
      m_section(std::move(section)),
      m_icon(std::move(icon)) {}

ObjectFactory::~ObjectFactory() = default;

ObjectFactory::Type ObjectFactory::getType() const { return m_type; }

QString ObjectFactory::getName() const { return m_name; }

QString ObjectFactory::getSection() const { return m_section; }

QIcon ObjectFactory::getIcon() const { return m_icon; }

/* ----------------------------------- Utils -------------------------------- */

ObjectFactory* getObjectFactoryByClassName(const QString& class_name) {
  auto& manager = egnite::PluginManager::getInstance();
  auto factory = manager.findIf<ObjectFactory>([class_name](auto factory) {
    return factory->getObjectClassName() == class_name;
  });

  return factory;
}

}  // namespace flow_document