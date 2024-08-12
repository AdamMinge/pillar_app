#ifndef AEGIS_SEARCH_COMMAND_CHILDREN_H
#define AEGIS_SEARCH_COMMAND_CHILDREN_H

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

/* ---------------------------- FoundChildrenMessage ------------------------ */

struct LIB_AEGIS_SERVER_API FoundChildrenMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QMap<QString, QStringList> children MEMBER children)

  QMap<QString, QStringList> children;
};

/* ------------------------------- ChildrenFinder --------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ChildrenFinder {
 public:
  using Result = Response<FoundChildrenMessage>;

 public:
  explicit ChildrenFinder();
  ~ChildrenFinder();

  Result find(const QString& id);
};

/* ------------------------------ ChildrenCommand --------------------------- */

class LIB_AEGIS_SEARCH_COMMAND_API ChildrenCommand : public Command {
 public:
  explicit ChildrenCommand(const CommandExecutor& manager);
  ~ChildrenCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  ChildrenFinder m_finder;
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_CHILDREN_H