#ifndef AEGIS_SNIFFER_COMMAND_SNIFFER_H
#define AEGIS_SNIFFER_COMMAND_SNIFFER_H

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

/* ---------------------------------- Sniffer ------------------------------- */

struct LIB_AEGIS_SERVER_API FoundObjectsMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QStringList objects MEMBER objects)

  QStringList objects;
};

/* ---------------------------------- Sniffer ------------------------------- */

class LIB_AEGIS_SNIFFER_COMMAND_API Finder {
 public:
  using Result = Response<FoundObjectsMessage>;

 public:
  explicit Finder(const ObjectSearcher& searcher);
  ~Finder();

  Result find(const QString& id);

 private:
  const ObjectSearcher& m_searcher;
};

/* ------------------------------- FindCommand ------------------------------ */

class LIB_AEGIS_SNIFFER_COMMAND_API FindCommand : public Command {
 public:
  explicit FindCommand(const CommandManager& manager);
  ~FindCommand() override;

  [[nodiscard]] QString getName() const override;

  [[nodiscard]] QByteArray exec(const QStringList& args) override;

 private:
  QCommandLineParser m_parser;
  Finder m_finder;
};

}  // namespace aegis

#endif  // AEGIS_SNIFFER_COMMAND_SNIFFER_H