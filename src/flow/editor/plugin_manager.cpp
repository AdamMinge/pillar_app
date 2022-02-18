/* ------------------------------------ Qt ---------------------------------- */
#include <QCoreApplication>
#include <QDirIterator>
#include <QPluginLoader>
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

void PluginManager::loadPlugins(QString plugins_path)
{
  m_plugins.clear();

  auto static_plugin_instances = QPluginLoader::staticInstances();
  for (auto instance : static_plugin_instances) { Plugin::create(instance); }

  if(plugins_path.isEmpty())
  {
    plugins_path = QCoreApplication::applicationDirPath();
    plugins_path += QStringLiteral("/plugins");
  }

  auto plugin_iterator =
    QDirIterator(plugins_path, QDir::Files | QDir::Readable);
  while (plugin_iterator.hasNext())
  {
    const auto plugin_file = plugin_iterator.next();
    if (!QLibrary::isLibrary(plugin_file)) continue;

    auto plugin = Plugin::create(plugin_file);
    m_plugins.push_back(std::move(plugin));
  }
}

std::list<Plugin*> PluginManager::getPlugins()
{
  auto plugins = std::list<Plugin *>{};
  std::transform(m_plugins.begin(), m_plugins.end(),
                 std::back_inserter(plugins),
                 [](auto &plugin) { return &plugin; });
  return plugins;
}

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
