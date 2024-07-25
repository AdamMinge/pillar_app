#ifndef FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H
#define FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/script_module.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API FlowScriptModule : public pillar::ScriptModule {
  Q_OBJECT
  Q_INTERFACES(pillar::ScriptModule)

 public:
  explicit FlowScriptModule(QObject *parent = nullptr);
  ~FlowScriptModule() override;

  [[nodiscard]] QString getName() const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H
