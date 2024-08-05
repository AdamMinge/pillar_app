#ifndef AEGIS_SNIFFER_COMMAND_CHILDREN_H
#define AEGIS_SNIFFER_COMMAND_CHILDREN_H

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

/* ---------------------------- FoundChildrenMessage ------------------------ */

struct LIB_AEGIS_SERVER_API FoundChildrenMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QMap<QString, QStringList> children MEMBER children)

  QMap<QString, QStringList> children;
};

/* ------------------------------- ChildrenFinder --------------------------- */

class LIB_AEGIS_SNIFFER_COMMAND_API ChildrenFinder {
 public:
  using Result = Response<FoundChildrenMessage>;

 public:
  explicit ChildrenFinder(const ObjectSearcher& searcher);
  ~ChildrenFinder();

  Result find(const QString& id);

 private:
  const ObjectSearcher& m_searcher;
};

/* ------------------------------ ChildrenCommand --------------------------- */

class LIB_AEGIS_SNIFFER_COMMAND_API ChildrenCommand : public Command {
 public:
  explicit ChildrenCommand(const CommandManager& manager);
  ~ChildrenCommand() override;

  [[nodiscard]] QString getName() const override;

  [[nodiscard]] QByteArray exec(const QStringList& args) override;

 private:
  QCommandLineParser m_parser;
  ChildrenFinder m_finder;
};

}  // namespace aegis

#endif  // AEGIS_SNIFFER_COMMAND_CHILDREN_H