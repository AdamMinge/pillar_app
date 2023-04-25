#ifndef EGNITE_SCRIPT_MODULE_H
#define EGNITE_SCRIPT_MODULE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LIB_EGNITE_API ScriptModule : public QObject {
  Q_OBJECT

 public:
  explicit ScriptModule(QObject *parent = nullptr);
  ~ScriptModule() override;

  Q_INVOKABLE [[nodiscard]] virtual QString getName() const = 0;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::ScriptModule, "org.egnite.ScriptModule")

#endif  // EGNITE_SCRIPT_MODULE_H
