/* ----------------------------------- Local -------------------------------- */
#include "aegis/command/recorder.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QMetaEnum>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------------- Recorder ------------------------------ */

Recorder::Recorder(QObject *parent) : QObject(parent) {}

Recorder::RecorderResult Recorder::start() {
  return RecorderSuccess(QLatin1String(""));
}

Recorder::RecorderResult Recorder::pause() {
  return RecorderSuccess(QLatin1String(""));
}

Recorder::RecorderResult Recorder::stop() {
  return RecorderSuccess(QLatin1String(""));
}

Recorder::RecorderResult Recorder::report() {
  return RecorderSuccess(QLatin1String(""));
}

bool Recorder::eventFilter(QObject *obj, QEvent *event) {
  return QObject::eventFilter(obj, event);
}

/* ------------------------------ RecorderCommand --------------------------- */

RecorderCommand::RecorderCommand(const Serializer &serializer)
    : Command(serializer) {
  m_parser.setApplicationDescription("Recorder");
  m_parser.addHelpOption();
  m_parser.addOptions({
      {{"s", "start"}, "Start the Recorder"},
      {{"p", "pause"}, "Pause the Recorder"},
      {{"t", "stop"}, "Stop the Recorder"},
      {{"r", "report"}, "Report the Recorder"},

  });
}

RecorderCommand::~RecorderCommand() = default;

QLatin1String RecorderCommand::name() { return QLatin1String("RECORDER"); }

QByteArray RecorderCommand::exec(const QStringList &args) {
  if (m_parser.parse(args)) {
    if (m_parser.isSet("start")) return serialize(m_recorder.start());
    if (m_parser.isSet("pause")) return serialize(m_recorder.pause());
    if (m_parser.isSet("stop")) return serialize(m_recorder.stop());
    if (m_parser.isSet("report")) return serialize(m_recorder.report());
  }

  auto error = ErrorResponse(QLatin1String("Recorder Command Error"),
                             m_parser.errorText());
  return serialize(error);
}

}  // namespace aegis
