#ifndef AEGIS_RECORDER_COMMAND_RECORD_H
#define AEGIS_RECORDER_COMMAND_RECORD_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Recorder;

/* ------------------------------- RecordCommand ---------------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordCommand : public Command {
 public:
  enum class State { Running, Paused, Stopped };

 public:
  explicit RecordCommand();
  ~RecordCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  Response<> start();
  Response<> pause();
  Response<> stop();
  Response<> report();

 private:
  State m_state;
  QScopedPointer<Recorder> m_recorder;
};

}  // namespace aegis

#endif  // AEGIS_RECORDER_COMMAND_RECORD_H