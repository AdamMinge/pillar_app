#ifndef AEGIS_SERVER_COMMAND_RECORDER_H
#define AEGIS_SERVER_COMMAND_RECORDER_H

/* ----------------------------------- Boost -------------------------------- */
#include <QCommandLineParser>
#include <QObject>
/* ----------------------------------- Aegis -------------------------------- */
#include <aegis/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/command/command.h"
#include "aegis_server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis_server {

/* ---------------------------------- Recorder ------------------------------ */

class LIB_AEGIS_SERVER_API Recorder : public QObject {
  Q_OBJECT

 public:
  using Result = aegis::Response<>;

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

class LIB_AEGIS_API RecorderCommand : public Command {
 public:
  [[nodiscard]] static QLatin1String name();

 public:
  explicit RecorderCommand(const aegis::Serializer &serializer);
  ~RecorderCommand() override;

  QByteArray exec(const QStringList &args) override;

 private:
  QCommandLineParser m_parser;
  Recorder m_recorder;
};

}  // namespace aegis_server

#endif  // AEGIS_SERVER_COMMAND_RECORDER_H