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

/* ----------------------------- FoundParentMessage ------------------------- */

struct LIB_AEGIS_SERVER_API FoundParentMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QMap<QString, QString> parents MEMBER parents)

  QMap<QString, QString> parents;
};

/* -------------------------------- ParentFinder ---------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ParentFinder {
 public:
  using Result = Response<FoundParentMessage>;

 public:
  explicit ParentFinder();
  ~ParentFinder();

  Result find(const QString& id);
};

/* ------------------------------ ParentCommand ----------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ParentCommand : public Command {
 public:
  explicit ParentCommand(const CommandExecutor& manager);
  ~ParentCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  ParentFinder m_finder;
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_PARENT_H