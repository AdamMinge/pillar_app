#ifndef FLOW_FLOW_SCRIPT_MODULE_H
#define FLOW_FLOW_SCRIPT_MODULE_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/script_module.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class LIB_FLOW_API FlowScriptModule : public flow::ScriptModule
{
  Q_OBJECT
  Q_INTERFACES(flow::ScriptModule)

public:
  explicit FlowScriptModule(QObject *parent = nullptr);
  ~FlowScriptModule() override;

  [[nodiscard]] QString getName() const override;
};

#endif//FLOW_FLOW_SCRIPT_MODULE_H
