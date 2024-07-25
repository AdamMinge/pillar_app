#ifndef AEGIS_SERVER_COMMAND_RECORDER_H
#define AEGIS_SERVER_COMMAND_RECORDER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"
#include "aegis/server/export.h"
#include "aegis/server/response.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------------- Recorder ------------------------------ */

class LIB_AEGIS_SERVER_API Recorder : public QObject {
  Q_OBJECT

 public:
  using Result = Response<>;

 public:
  explicit Recorder(QObject *parent = nullptr);

  Result start();
  Result pause();
  Result stop();
  Result report();

 protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

 private:
};

/* ------------------------------ RecorderCommand --------------------------- */

class LIB_AEGIS_SERVER_API RecorderCommand : public Command {
 public:
  [[nodiscard]] static QLatin1String name();

 public:
  explicit RecorderCommand(const ResponseSerializer &serializer);
  ~RecorderCommand() override;

  QByteArray exec(const QStringList &args) override;

 private:
  QCommandLineParser m_parser;
  Recorder m_recorder;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_RECORDER_H