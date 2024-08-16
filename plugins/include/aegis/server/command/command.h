#ifndef AEGIS_SERVER_COMMAND_COMMAND_H
#define AEGIS_SERVER_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
#include <QCommandLineParser>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
class OArchive;
}

namespace aegis {

/* ------------------------------- HelpMessage ------------------------------ */

struct LIB_AEGIS_SERVER_API HelpMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QString help MEMBER help)

  QString help;
};

/* ---------------------------------- Command ------------------------------- */

class LIB_AEGIS_SERVER_API Command {
 public:
  explicit Command(const QString& name);
  virtual ~Command();

  [[nodiscard]] QByteArray exec(const QStringList& args);

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getError() const;
  [[nodiscard]] QString getHelp() const;

 protected:
  [[nodiscard]] virtual QByteArray exec() = 0;

 protected:
  QString m_name;
  QCommandLineParser m_parser;
  QStringList m_required_options;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H