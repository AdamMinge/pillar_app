#ifndef FLOW_PLUGIN_MANAGER_H
#define FLOW_PLUGIN_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QScopedPointer>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/plugin.h"
/* -------------------------------------------------------------------------- */


class PluginManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static PluginManager &getInstance();
  static void deleteInstance();

public:
  ~PluginManager() override;

  void loadPlugins(QString plugins_path = {});
  [[nodiscard]] std::list<Plugin *> getPlugins();

  void addObject(QObject *object);
  void removeObject(QObject *object);

  template<typename TYPE>
  void forEach(const std::function<void(TYPE *)> &function);
  template<typename TYPE>
  TYPE *forOne(const std::function<bool(TYPE *)> &function);
  template<typename TYPE>
  [[nodiscard]] QList<TYPE *> getObjects();

Q_SIGNALS:
  void objectAdded(QObject *object);
  void objectRemoved(QObject *object);

protected:
  explicit PluginManager();

private:
  static QScopedPointer<PluginManager> m_instance;

  QObjectList m_objects;
  std::list<Plugin> m_plugins;
};

template<typename TYPE>
void PluginManager::forEach(const std::function<void(TYPE *)> &function)
{
  for (auto object : m_objects)
  {
    if (auto result = qobject_cast<TYPE *>(object); result) function(result);
  }
}

template<typename TYPE>
TYPE *PluginManager::forOne(const std::function<bool(TYPE *)> &function)
{
  for (auto object : m_objects)
  {
    if (auto result = qobject_cast<TYPE *>(object); result)
    {
      if (function(result)) return result;
    }
  }

  return nullptr;
}

template<typename TYPE>
QList<TYPE *> PluginManager::getObjects()
{
  QList<TYPE *> objects{};
  for (auto object : m_objects)
  {
    if (auto result = qobject_cast<TYPE *>(object); result)
      objects.append(result);
  }

  return objects;
}

#endif//FLOW_PLUGIN_MANAGER_H
