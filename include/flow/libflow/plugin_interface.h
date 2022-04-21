#ifndef FLOW_PLUGIN_INTERFACE_H
#define FLOW_PLUGIN_INTERFACE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{

  class LIB_FLOW_API PluginInterface : public QObject
  {
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

}// namespace flow

Q_DECLARE_INTERFACE(flow::PluginInterface, "org.flow.PluginInterface")

#endif//FLOW_PLUGIN_INTERFACE_H
