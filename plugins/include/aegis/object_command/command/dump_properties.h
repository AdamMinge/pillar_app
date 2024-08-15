#ifndef AEGIS_OBJECT_COMMAND_COMMAND_DUMP_PROPERTIES_H
#define AEGIS_OBJECT_COMMAND_COMMAND_DUMP_PROPERTIES_H

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

/* --------------------------- PropertiesDumpMessage ------------------------ */

struct LIB_AEGIS_OBJECT_COMMAND_API PropertiesDumpMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QString object MEMBER object)
  Q_PROPERTY(QMap<QString, QVariant> properties MEMBER properties)

  [[nodiscard]] bool operator==(const PropertiesDumpMessage& other) const;
  [[nodiscard]] bool operator!=(const PropertiesDumpMessage& other) const;

  QString object;
  QMap<QString, QVariant> properties;
};

/* -------------------------- PropertiesDumpsMessage ----------------------- */

struct LIB_AEGIS_OBJECT_COMMAND_API PropertiesDumpsMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QList<PropertiesDumpMessage> objects MEMBER objects)

  QList<PropertiesDumpMessage> objects;
};

/* ----------------------------- PropertiesDumper --------------------------- */

class LIB_AEGIS_OBJECT_COMMAND_API PropertiesDumper {
 public:
  using Result = Response<PropertiesDumpsMessage>;

 public:
  explicit PropertiesDumper();
  ~PropertiesDumper();

  Result dump(const QString& id) const;

 private:
  [[nodiscard]] QMap<QString, QVariant> getProperties(
      const QObject* object) const;
};

/* --------------------------- DumpPropertiesCommand ------------------------ */

class LIB_AEGIS_OBJECT_COMMAND_API DumpPropertiesCommand : public Command {
 public:
  explicit DumpPropertiesCommand();
  ~DumpPropertiesCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  PropertiesDumper m_dumper;
};

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_COMMAND_DUMP_PROPERTIES_H
