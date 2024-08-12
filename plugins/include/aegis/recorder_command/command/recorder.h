#ifndef AEGIS_RECORDER_COMMAND_RECORDER_H
#define AEGIS_RECORDER_COMMAND_RECORDER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/export.h"
/* -------------------------------------------------------------------------- */

class QMouseEvent;
class QKeyEvent;
class QWheelEvent;

namespace aegis {

namespace event {

struct MouseButtonEvent {
  QPoint pos;
  Qt::MouseButton button;
  Qt::MouseButtons buttons;
  Qt::KeyboardModifiers modifiers;
};

struct MouseButtonPressEvent : public MouseButtonEvent {};

struct MouseButtonReleaseEvent : public MouseButtonEvent {};

struct MouseMoveEvent {
  QPoint pos;
  Qt::MouseButtons buttons;
  Qt::KeyboardModifiers modifiers;
};

struct MouseWheelEvent {
  QPoint angle;
  Qt::KeyboardModifiers modifiers;
};

struct KeyEvent {
  int key;
  Qt::KeyboardModifiers modifiers;
  QString text;
};

struct KeyPressEvent : public KeyEvent {};

struct KeyReleaseEvent : public KeyEvent {};

}  // namespace event

/* ---------------------------------- Recorder ------------------------------ */

class LIB_AEGIS_RECORDER_COMMAND_API Recorder : public QObject {
  Q_OBJECT

 public:
  using Result = Response<>;
  enum class State { Running, Paused, Stopped };

 public:
  explicit Recorder(QString error, QObject* parent = nullptr);
  ~Recorder() override;

  Result start();
  Result pause();
  Result stop();
  Result report();

 protected:
  bool eventFilter(QObject* obj, QEvent* event) override;

 private:
  void recordMouseButtonPress(QObject* obj, QMouseEvent* event);
  void recordMouseButtonRelease(QObject* obj, QMouseEvent* event);
  void recordMouseMove(QObject* obj, QMouseEvent* event);
  void recordMouseWheel(QObject* obj, QWheelEvent* event);

  void recordKeyPress(QObject* obj, QKeyEvent* event);
  void recordKeyRelease(QObject* obj, QKeyEvent* event);

  template <typename TYPE>
  requires std::is_rvalue_reference_v<TYPE&&>
  void recordEvent(TYPE&& event);

 private:
  QString m_error;
  State m_state;
  QList<QVariant> m_events;
};

template <typename TYPE>
requires std::is_rvalue_reference_v<TYPE&&>
void Recorder::recordEvent(TYPE&& event) {
  auto variant = QVariant::fromValue(std::forward<TYPE>(event));
  if (m_events.size() > 0 && m_events.back().canConvert<TYPE>()) {
    m_events.back() = std::move(variant);
  } else {
    m_events.push_back(std::move(variant));
  }
}

/* ------------------------------ RecorderCommand --------------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecorderCommand : public Command {
 public:
  explicit RecorderCommand(const CommandExecutor& manager);
  ~RecorderCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  Recorder m_recorder;
};

}  // namespace aegis

Q_DECLARE_METATYPE(aegis::event::MouseButtonPressEvent)
Q_DECLARE_METATYPE(aegis::event::MouseButtonReleaseEvent)
Q_DECLARE_METATYPE(aegis::event::MouseMoveEvent)
Q_DECLARE_METATYPE(aegis::event::MouseWheelEvent)
Q_DECLARE_METATYPE(aegis::event::KeyPressEvent)
Q_DECLARE_METATYPE(aegis::event::KeyReleaseEvent)

#endif  // AEGIS_RECORDER_COMMAND_RECORDER_H