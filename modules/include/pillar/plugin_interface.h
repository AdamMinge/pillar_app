#ifndef PILLAR_PLUGIN_INTERFACE_H
#define PILLAR_PLUGIN_INTERFACE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class LIB_PILLAR_API PluginInterface : public QObject {
  Q_OBJECT

 public:
  explicit PluginInterface();
  ~PluginInterface() override;

  virtual void init();

 protected:
  void addObject(QObject *object);
  void removeObject(QObject *object);

 private:
  QList<QObject *> m_added_objects;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::PluginInterface, "org.pillar.PluginInterface")

#endif  // PILLAR_PLUGIN_INTERFACE_H
