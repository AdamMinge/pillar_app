#ifndef AEGIS_OBJECT_COMMAND_COMMAND_DUMP_METHODS_H
#define AEGIS_OBJECT_COMMAND_COMMAND_DUMP_METHODS_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
#include <QStringList>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- MethodsDumpMessage -------------------------- */

struct LIB_AEGIS_OBJECT_COMMAND_API MethodsDumpMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QString object MEMBER object)
  Q_PROPERTY(QStringList methods MEMBER methods)

  [[nodiscard]] bool operator==(const MethodsDumpMessage& other) const;
  [[nodiscard]] bool operator!=(const MethodsDumpMessage& other) const;

  QString object;
  QStringList methods;
};

/* --------------------------- MethodsDumpsMessage ------------------------- */

struct LIB_AEGIS_OBJECT_COMMAND_API MethodsDumpsMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QList<MethodsDumpMessage> objects MEMBER objects)

  QList<MethodsDumpMessage> objects;
};

/* ---------------------------- DumpMethodsCommand -------------------------- */

class LIB_AEGIS_OBJECT_COMMAND_API DumpMethodsCommand : public Command {
 public:
  explicit DumpMethodsCommand();
  ~DumpMethodsCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  [[nodiscard]] Response<MethodsDumpsMessage> dump(const QString& id) const;
  [[nodiscard]] QStringList getMethods(const QObject* object) const;
};

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_COMMAND_DUMP_METHODS_H
