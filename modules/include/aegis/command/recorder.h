#ifndef AEGIS_COMMAND_RECORDER_H
#define AEGIS_COMMAND_RECORDER_H

/* ----------------------------------- Boost -------------------------------- */
#include <QCommandLineParser>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/command/command.h"
#include "aegis/command/response.h"
#include "aegis/export.h"
#include "aegis/result.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------------- Recorder ------------------------------ */

class LIB_AEGIS_API Recorder : public QObject {
  Q_OBJECT

 public:
  using RecorderError = ErrorResponse;
  using RecorderSuccess = SuccessResponse<void>;
  using RecorderResult = Result<RecorderError, RecorderSuccess>;

 public:
  explicit Recorder(QObject *parent = nullptr);

  RecorderResult start();
  RecorderResult pause();
  RecorderResult stop();
  RecorderResult report();

 protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

 private:
};

/* ------------------------------ RecorderCommand --------------------------- */

class LIB_AEGIS_API RecorderCommand : public Command {
 public:
  [[nodiscard]] static QLatin1String name();

 public:
  explicit RecorderCommand(const Serializer &serializer);
  ~RecorderCommand() override;

  QByteArray exec(const QStringList &args) override;

 private:
  QCommandLineParser m_parser;
  Recorder m_recorder;
};

}  // namespace aegis

#endif  // AEGIS_COMMAND_RECORDER_H