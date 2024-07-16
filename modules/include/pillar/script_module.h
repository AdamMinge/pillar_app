#ifndef PILLAR_SCRIPT_MODULE_H
#define PILLAR_SCRIPT_MODULE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class LIB_PILLAR_API ScriptModule : public QObject {
  Q_OBJECT

 public:
  explicit ScriptModule(QObject *parent = nullptr);
  ~ScriptModule() override;

  Q_INVOKABLE [[nodiscard]] virtual QString getName() const = 0;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::ScriptModule, "org.pillar.ScriptModule")

#endif  // PILLAR_SCRIPT_MODULE_H
