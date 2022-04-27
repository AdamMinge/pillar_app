#ifndef FLOW_SCRIPT_MODULE_H
#define FLOW_SCRIPT_MODULE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{

  class LIB_FLOW_API ScriptModule : public QObject
  {
    Q_OBJECT

  public:
    explicit ScriptModule(QObject *parent = nullptr);
    ~ScriptModule() override;
  };

}// namespace flow

#endif//FLOW_SCRIPT_MODULE_H
