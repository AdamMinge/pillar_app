#ifndef AEGIS_SNIFFER_COMMAND_PARENT_H
#define AEGIS_SNIFFER_COMMAND_PARENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
#include <QObject>
#include <QTimer>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/sniffer_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class ObjectSearcher;

/* ----------------------------- FoundParentMessage ------------------------- */

struct LIB_AEGIS_SERVER_API FoundParentMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QMap<QString, QString> parents MEMBER parents)

  QMap<QString, QString> parents;
};

/* -------------------------------- ParentFinder ---------------------------- */

class LIB_AEGIS_SNIFFER_COMMAND_API ParentFinder {
 public:
  using Result = Response<FoundParentMessage>;

 public:
  explicit ParentFinder(const ObjectSearcher& searcher);
  ~ParentFinder();

  Result find(const QString& id);

 private:
  const ObjectSearcher& m_searcher;
};

/* ------------------------------ ParentCommand ----------------------------- */

class LIB_AEGIS_SNIFFER_COMMAND_API ParentCommand : public Command {
 public:
  explicit ParentCommand(const CommandManager& manager);
  ~ParentCommand() override;

  [[nodiscard]] QString getName() const override;

  [[nodiscard]] QByteArray exec(const QStringList& args) override;

 private:
  QCommandLineParser m_parser;
  ParentFinder m_finder;
};

}  // namespace aegis

#endif  // AEGIS_SNIFFER_COMMAND_PARENT_H