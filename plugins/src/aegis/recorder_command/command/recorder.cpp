/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/command/recorder.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
/* -------------------------------------------------------------------------- */

namespace aegis {

static constexpr QLatin1String recorder_error =
    QLatin1String("Recorder Command Error");

/* ---------------------------------- Recorder ------------------------------ */

Recorder::Recorder(QObject* parent) : QObject(parent), m_state(State::Stopped) {
  moveToThread(qApp->thread());
}

Recorder::~Recorder() = default;

Recorder::Result Recorder::start() {
  if (m_state == State::Running) {
    return ErrorMessage(
        recorder_error,
        QLatin1String(
            "The start cannot be triggered, the recorder is already working"));
  }

  qApp->installEventFilter(this);
  m_state = State::Running;

  return EmptyMessage();
}

Recorder::Result Recorder::pause() {
  if (m_state != State::Running) {
    return ErrorMessage(
        recorder_error,
        QLatin1String(
            "The pause cannot be triggered, the recorder is not working"));
  }

  qApp->removeEventFilter(this);
  m_state = State::Paused;

  return EmptyMessage();
}

Recorder::Result Recorder::stop() {
  if (m_state == State::Stopped) {
    return ErrorMessage(
        recorder_error,
        QLatin1String(
            "The stop cannot be triggered, the recorder is already stopped"));
  }

  qApp->removeEventFilter(this);
  m_state = State::Stopped;
  m_events.clear();

  return EmptyMessage();
}

Recorder::Result Recorder::report() { return EmptyMessage(); }

bool Recorder::eventFilter(QObject* obj, QEvent* event) {
  auto event_type = event->type();

  if (event_type == QEvent::MouseButtonPress)
    recordMouseButtonPress(obj, static_cast<QMouseEvent*>(event));
  else if (event_type == QEvent::MouseButtonRelease)
    recordMouseButtonRelease(obj, static_cast<QMouseEvent*>(event));
  else if (event_type == QEvent::MouseMove)
    recordMouseMove(obj, static_cast<QMouseEvent*>(event));
  else if (event_type == QEvent::Wheel)
    recordMouseWheel(obj, static_cast<QWheelEvent*>(event));
  else if (event_type == QEvent::KeyPress)
    recordKeyPress(obj, static_cast<QKeyEvent*>(event));
  else if (event_type == QEvent::KeyRelease)
    recordKeyRelease(obj, static_cast<QKeyEvent*>(event));

  return QObject::eventFilter(obj, event);
}

void Recorder::recordMouseButtonPress(QObject* obj, QMouseEvent* event) {
  auto record_event = event::MouseButtonPressEvent{};
  record_event.pos = event->pos();
  record_event.button = event->button();
  record_event.buttons = event->buttons();
  record_event.modifiers = event->modifiers();

  recordEvent(std::move(record_event));
}

void Recorder::recordMouseButtonRelease(QObject* obj, QMouseEvent* event) {
  auto record_event = event::MouseButtonReleaseEvent{};
  record_event.pos = event->pos();
  record_event.button = event->button();
  record_event.buttons = event->buttons();
  record_event.modifiers = event->modifiers();

  recordEvent(std::move(record_event));
}

void Recorder::recordMouseMove(QObject* obj, QMouseEvent* event) {
  auto record_event = event::MouseMoveEvent{};
  record_event.pos = event->pos();
  record_event.buttons = event->buttons();
  record_event.modifiers = event->modifiers();

  recordEvent(std::move(record_event));
}

void Recorder::recordMouseWheel(QObject* obj, QWheelEvent* event) {
  auto record_event = event::MouseWheelEvent{};
  record_event.angle = event->angleDelta();
  record_event.modifiers = event->modifiers();

  recordEvent(std::move(record_event));
}

void Recorder::recordKeyPress(QObject* obj, QKeyEvent* event) {
  auto record_event = event::KeyPressEvent{};
  record_event.key = event->key();
  record_event.modifiers = event->modifiers();
  record_event.text = event->text();

  recordEvent(std::move(record_event));
}

void Recorder::recordKeyRelease(QObject* obj, QKeyEvent* event) {
  auto record_event = event::KeyReleaseEvent{};
  record_event.key = event->key();
  record_event.modifiers = event->modifiers();
  record_event.text = event->text();

  recordEvent(std::move(record_event));
}

/* ------------------------------ RecorderCommand --------------------------- */

RecorderCommand::RecorderCommand(const CommandExecutor& manager)
    : Command(manager) {
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

QByteArray RecorderCommand::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error = Response<>(ErrorMessage(recorder_error, m_parser.errorText()));
    return serialize(error);
  }

  if (m_parser.isSet("start")) return serialize(m_recorder.start());
  if (m_parser.isSet("pause")) return serialize(m_recorder.pause());
  if (m_parser.isSet("stop")) return serialize(m_recorder.stop());
  if (m_parser.isSet("report")) return serialize(m_recorder.report());

  auto error = Response<>(ErrorMessage(
      recorder_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
