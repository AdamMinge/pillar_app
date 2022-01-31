#ifndef FLOW_PLUGIN_MANAGER_H
#define FLOW_PLUGIN_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QScopedPointer>
/* -------------------------------------------------------------------------- */

class PluginManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static PluginManager &getInstance();
  static void deleteInstance();

public:
  ~PluginManager() override;

  void addObject(QObject *object);
  void removeObject(QObject *object);

  template<typename TYPE>
  void forEach(const std::function<void(TYPE *)> &function);
  template<typename TYPE>
  TYPE *forOne(const std::function<bool(TYPE *)> &function);
  template<typename TYPE>
  QList<TYPE *> getObjects();

Q_SIGNALS:
  void objectAdded(QObject *object);
  void objectRemoved(QObject *object);

protected:
  explicit PluginManager();

private:
  static QScopedPointer<PluginManager> m_instance;

  QObjectList m_objects;
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
    if (auto result = qobject_cast<TYPE>(object); result)
      objects.append(result);
  }

  return objects;
}

#endif//FLOW_PLUGIN_MANAGER_H
