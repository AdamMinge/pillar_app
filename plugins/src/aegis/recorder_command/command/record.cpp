/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/command/record.h"

#include "aegis/recorder_command/record/recorder.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------- RecordCommand ---------------------------- */

RecordCommand::RecordCommand()
    : Command(QLatin1String("Record")),
      m_state(State::Stopped),
      m_recorder(new Recorder) {
  m_parser.addOptions({
      {{"s", "start"}, "Start the Recorder"},
      {{"p", "pause"}, "Pause the Recorder"},
      {{"t", "stop"}, "Stop the Recorder"},
      {{"r", "report"}, "Report the Recorder"},
  });
}

RecordCommand::~RecordCommand() = default;

Response<> RecordCommand::report() { return EmptyMessage(); }

QByteArray RecordCommand::exec() {
  if (m_parser.isSet("start")) return serializer()->serialize(start());
  if (m_parser.isSet("pause")) return serializer()->serialize(pause());
  if (m_parser.isSet("stop")) return serializer()->serialize(stop());
  if (m_parser.isSet("report")) return serializer()->serialize(report());

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

Response<> RecordCommand::start() {
  if (m_state == State::Running) {
    return ErrorMessage(
        getError(),
        QLatin1String(
            "The start cannot be triggered, the recorder is already working"));
  }

  m_state = State::Running;
  m_recorder->start();

  return EmptyMessage();
}

Response<> RecordCommand::pause() {
  if (m_state != State::Running) {
    return ErrorMessage(
        getError(),
        QLatin1String(
            "The pause cannot be triggered, the recorder is not working"));
  }

  m_state = State::Paused;
  m_recorder->stop();

  return EmptyMessage();
}

Response<> RecordCommand::stop() {
  if (m_state == State::Stopped) {
    return ErrorMessage(
        getError(),
        QLatin1String(
            "The stop cannot be triggered, the recorder is already stopped"));
  }

  m_state = State::Stopped;
  m_recorder->stop();
  m_recorder->clear();

  return EmptyMessage();
}

}  // namespace aegis
