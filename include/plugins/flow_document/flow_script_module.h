#ifndef FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H
#define FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H

/* ----------------------------------- Flow --------------------------------- */
#include <flow/script_module.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class LIB_FLOW_API FlowScriptModule : public flow::ScriptModule {
  Q_OBJECT
  Q_INTERFACES(flow::ScriptModule)

 public:
  explicit FlowScriptModule(QObject *parent = nullptr);
  ~FlowScriptModule() override;

  [[nodiscard]] QString getName() const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H
