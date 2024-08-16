#ifndef AEGIS_OBJECT_COMMAND_COMMAND_INVOKE_METHOD_H
#define AEGIS_OBJECT_COMMAND_COMMAND_INVOKE_METHOD_H

/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- InvokeMethodCommand ------------------------ */

class LIB_AEGIS_OBJECT_COMMAND_API InvokeMethodCommand : public Command {
 public:
  explicit InvokeMethodCommand();
  ~InvokeMethodCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  [[nodiscard]] Response<> invokeMethod(const QString& id, const QString& name,
                                        const QStringList& values);

  [[nodiscard]] QMetaMethod getMethod(const QObject* object,
                                      const QString& name) const;
};

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_COMMAND_INVOKE_METHOD_H
