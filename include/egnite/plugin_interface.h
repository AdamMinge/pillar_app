#ifndef EGNITE_PLUGIN_INTERFACE_H
#define EGNITE_PLUGIN_INTERFACE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LIB_EGNITE_API PluginInterface : public QObject {
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

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::PluginInterface, "org.egnite.PluginInterface")

#endif  // EGNITE_PLUGIN_INTERFACE_H
