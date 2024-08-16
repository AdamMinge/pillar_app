#ifndef AEGIS_SEARCH_COMMAND_PARENT_H
#define AEGIS_SEARCH_COMMAND_PARENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QTimer>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class ObjectQuery;

/* ----------------------------- ObjectParentMessage ------------------------ */

struct LIB_AEGIS_SEARCH_COMMAND_API ObjectParentMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QString object MEMBER object)
  Q_PROPERTY(QString parent MEMBER parent)

  [[nodiscard]] bool operator==(const ObjectParentMessage& other) const;
  [[nodiscard]] bool operator!=(const ObjectParentMessage& other) const;

  QString object;
  QString parent;
};

/* ---------------------------- ObjectsParentMessage ------------------------ */

struct LIB_AEGIS_SEARCH_COMMAND_API ObjectsParentMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QList<ObjectParentMessage> objects MEMBER objects)

  QList<ObjectParentMessage> objects;
};

/* ------------------------------ ParentCommand ----------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ParentCommand : public Command {
 public:
  explicit ParentCommand();
  ~ParentCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  [[nodiscard]] Response<ObjectsParentMessage> find(
      const ObjectQuery& query) const;
  [[nodiscard]] ObjectQuery getParent(const QObject* object) const;
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_PARENT_H