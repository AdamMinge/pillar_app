#ifndef FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H
#define FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/script_module.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API FlowScriptModule : public egnite::ScriptModule {
  Q_OBJECT
  Q_INTERFACES(egnite::ScriptModule)

 public:
  explicit FlowScriptModule(QObject *parent = nullptr);
  ~FlowScriptModule() override;

  [[nodiscard]] QString getName() const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_SCRIPT_MODULE_H
