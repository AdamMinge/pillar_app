/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/command/recorder.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QMetaEnum>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------------- Recorder ------------------------------ */

Recorder::Recorder(QObject *parent) : QObject(parent) {}

Recorder::Result Recorder::start() { return EmptyMessage(); }

Recorder::Result Recorder::pause() { return EmptyMessage(); }

Recorder::Result Recorder::stop() { return EmptyMessage(); }

Recorder::Result Recorder::report() { return EmptyMessage(); }

bool Recorder::eventFilter(QObject *obj, QEvent *event) {
  return QObject::eventFilter(obj, event);
}

/* ------------------------------ RecorderCommand --------------------------- */

RecorderCommand::RecorderCommand(const ResponseSerializer &serializer)
    : Command(serializer) {
  m_parser.addHelpOption();
  m_parser.addOptions({
      {{"s", "start"}, "Start the Recorder"},
      {{"p", "pause"}, "Pause the Recorder"},
      {{"t", "stop"}, "Stop the Recorder"},
      {{"r", "report"}, "Report the Recorder"},

  });
}

RecorderCommand::~RecorderCommand() = default;

QString RecorderCommand::getName() const { return QString("Recorder"); }

QByteArray RecorderCommand::exec(const QStringList &args) {
  if (m_parser.parse(args)) {
    if (m_parser.isSet("start")) return serialize(m_recorder.start());
    if (m_parser.isSet("pause")) return serialize(m_recorder.pause());
    if (m_parser.isSet("stop")) return serialize(m_recorder.stop());
    if (m_parser.isSet("report")) return serialize(m_recorder.report());
  }

  auto error = Response<>(ErrorMessage(QLatin1String("Recorder Command Error"),
                                       m_parser.errorText()));
  return serialize(error);
}

}  // namespace aegis
