/* ----------------------------------- Local -------------------------------- */
#include "flow/document/flow/factory/object_factory.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------- ObjectFactory ---------------------------- */

ObjectFactory::ObjectFactory(QString type, QString name, QString section,
                             QIcon icon, QObject* parent)
    : QObject(parent),
      m_type(std::move(type)),
      m_name(std::move(name)),
      m_section(std::move(section)),
      m_icon(std::move(icon)) {}

ObjectFactory::~ObjectFactory() = default;

QString ObjectFactory::getType() const { return m_type; }

QString ObjectFactory::getName() const { return m_name; }

QString ObjectFactory::getSection() const { return m_section; }

QIcon ObjectFactory::getIcon() const { return m_icon; }

/* ----------------------------------- Qtils -------------------------------- */

ObjectFactory* getObjectFactoryByClassName(const QString& class_name) {
  auto& manager = pillar::PluginManager::getInstance();
  auto factory = manager.findIf<ObjectFactory>([class_name](auto factory) {
    return factory->getObjectClassName() == class_name;
  });

  return factory;
}

}  // namespace flow