#ifndef FLOW_PLUGIN_MANAGER_H
#define FLOW_PLUGIN_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QScopedPointer>
/* ----------------------------------- Local -------------------------------- */
#include "flow/export.h"
#include "flow/plugin.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_API PluginManager : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static PluginManager &getInstance();
  static void deleteInstance();

 public:
  ~PluginManager() override;

  void setDefaultPluginsPaths(QStringList plugins_paths);
  [[nodiscard]] QStringList getDefaultPluginsPaths() const;

  void loadPlugins(const QStringList &plugins_paths = {});
  [[nodiscard]] std::list<Plugin *> getPlugins();
  [[nodiscard]] std::list<Plugin *> getStaticPlugins();
  [[nodiscard]] std::list<Plugin *> getDynamicPlugins();

  void addObject(QObject *object);
  void removeObject(QObject *object);

  template <typename TYPE>
  void forEach(const std::function<void(TYPE *)> &function);
  template <typename TYPE>
  TYPE *forOne(const std::function<bool(TYPE *)> &function);
  template <typename TYPE>
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
  QStringList m_default_plugins_paths;
};

template <typename TYPE>
void PluginManager::forEach(const std::function<void(TYPE *)> &function) {
  for (auto object : m_objects) {
    if (auto result = qobject_cast<TYPE *>(object); result) function(result);
  }
}

template <typename TYPE>
TYPE *PluginManager::forOne(const std::function<bool(TYPE *)> &function) {
  for (auto object : m_objects) {
    if (auto result = qobject_cast<TYPE *>(object); result) {
      if (function(result)) return result;
    }
  }

  return nullptr;
}

template <typename TYPE>
QList<TYPE *> PluginManager::getObjects() {
  QList<TYPE *> objects{};
  for (auto object : m_objects) {
    if (auto result = qobject_cast<TYPE *>(object); result)
      objects.append(result);
  }

  return objects;
}

}  // namespace flow

#endif  // FLOW_PLUGIN_MANAGER_H
