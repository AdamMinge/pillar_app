#ifndef FLOW_SCRIPT_MODULE_H
#define FLOW_SCRIPT_MODULE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_API ScriptModule : public QObject {
  Q_OBJECT

 public:
  explicit ScriptModule(QObject *parent = nullptr);
  ~ScriptModule() override;

  Q_INVOKABLE [[nodiscard]] virtual QString getName() const = 0;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::ScriptModule, "org.flow.ScriptModule")

#endif  // FLOW_SCRIPT_MODULE_H
