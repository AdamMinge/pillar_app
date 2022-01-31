/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/plugin_manager.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<PluginManager> PluginManager::m_instance =
  QScopedPointer<PluginManager>(nullptr);

PluginManager &PluginManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new PluginManager);

  return *m_instance;
}

void PluginManager::deleteInstance() { m_instance.reset(nullptr); }

PluginManager::~PluginManager() = default;

PluginManager::PluginManager() = default;

void PluginManager::addObject(QObject *object)
{
  Q_ASSERT(object);

  m_objects.append(object);
  Q_EMIT objectAdded(object);
}

void PluginManager::removeObject(QObject *object)
{
  Q_ASSERT(object);

  m_objects.removeOne(object);
  Q_EMIT objectRemoved(object);
}