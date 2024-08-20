/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/record/recorder.h"

#include "aegis/recorder_command/record/strategy.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractButton>
#include <QApplication>
#include <QComboBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QTabBar>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------ Find Exceptions --------------------------- */

[[nodiscard]] QWidget *findScrollAreaException(QWidget *widget) {
  const auto is_scrollarea_viewport =
      widget->objectName() == QLatin1String("qt_scrollarea_viewport");
  if (is_scrollarea_viewport) widget = widget->parentWidget();

  return widget;
}

[[nodiscard]] QWidget *findComboBoxException(QWidget *widget) {
  const auto class_name = widget->metaObject()->className();
  const auto is_combobox_internal =
      class_name == QLatin1String("QComboBoxPrivateContainer") ||
      class_name == QLatin1String("QComboBoxListView");

  while (is_combobox_internal) {
    if (auto combobox = qobject_cast<QComboBox *>(widget); combobox) break;

    widget = widget->parentWidget();
    Q_ASSERT(widget);
  };

  return widget;
}

[[nodiscard]] QWidget *findTabBarException(QWidget *widget) {
  const auto is_close_button =
      widget->metaObject()->className() == QLatin1String("CloseButton");

  if (is_close_button) {
    auto tabbar = qobject_cast<QTabBar *>(widget->parentWidget());
    widget = tabbar ? tabbar : widget;
  }

  return widget;
}

/* ------------------------------- WidgetListener --------------------------- */

WidgetListener::WidgetListener(QObject *parent)
    : QObject(parent), m_current_widget(nullptr) {
  moveToThread(qApp->thread());
}

WidgetListener::~WidgetListener() = default;

bool WidgetListener::eventFilter(QObject *obj, QEvent *event) {
  switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::KeyPress:
    case QEvent::KeyRelease: {
      auto widget = findWidget(qobject_cast<QWidget *>(obj));
      setWidget(widget);
      break;
    }
  }

  return QObject::eventFilter(obj, event);
}

void WidgetListener::setWidget(QWidget *widget) {
  if (m_current_widget != widget) {
    m_current_widget = widget;
    Q_EMIT currentWidgetChanged(widget);
  }
}

QWidget *WidgetListener::findWidget(QWidget *widget) const {
  static const auto find_exceptions = {
      &findScrollAreaException, &findComboBoxException, &findTabBarException};

  if (widget) {
    for (const auto find_exception : find_exceptions) {
      widget = find_exception(widget);
    }
  }

  return widget;
}

/* ---------------------------------- Recorder ------------------------------ */

Recorder::Recorder(QObject *parent)
    : QObject(parent),
      m_current_strategy(nullptr),
      m_widget_listener(new WidgetListener(this)),
      m_running(false) {
  m_strategies.insert({
      {RecordButtonStrategy::type, new RecordButtonStrategy(this)},
      {RecordComboBoxStrategy::type, new RecordComboBoxStrategy(this)},
      {RecordSpinBoxStrategy::type, new RecordSpinBoxStrategy(this)},
      {RecordSliderStrategy::type, new RecordSliderStrategy(this)},
      {RecordTabBarStrategy::type, new RecordTabBarStrategy(this)},
      {RecordToolBoxStrategy::type, new RecordToolBoxStrategy(this)},
      {RecordMenuStrategy::type, new RecordMenuStrategy(this)},
      {RecordTextEditStrategy::type, new RecordTextEditStrategy(this)},
      {RecordLineEditStrategy::type, new RecordLineEditStrategy(this)},
      {RecordItemViewStrategy::type, new RecordItemViewStrategy(this)},
  });

  connect(m_widget_listener, &WidgetListener::currentWidgetChanged, this,
          &Recorder::onCurrentWidgetChanged);
}

Recorder::~Recorder() = default;

void Recorder::start() {
  Q_ASSERT(!m_running);

  qApp->installEventFilter(m_widget_listener);

  m_running = true;
}

void Recorder::stop() {
  Q_ASSERT(m_running);

  qApp->removeEventFilter(m_widget_listener);
  onCurrentWidgetChanged(nullptr);

  m_running = false;
}

void Recorder::clear() { m_report.clear(); }

const QStringList &Recorder::getReport() const { return m_report; }

void Recorder::onRecorder(const QString &command) {
  if (!m_running) return;
  m_report.append(command);
}

void Recorder::onCurrentWidgetChanged(QWidget *widget) {
  auto strategy = findStrategy(widget);

  if (m_current_strategy) {
    m_current_strategy->setWidget(nullptr);

    disconnect(m_current_strategy, &RecordStrategy::recorded, this,
               &Recorder::onRecorder);
  }

  m_current_strategy = strategy;

  if (m_current_strategy) {
    m_current_strategy->setWidget(widget);

    connect(m_current_strategy, &RecordStrategy::recorded, this,
            &Recorder::onRecorder);
  }
}

RecordStrategy *Recorder::findStrategy(QWidget *widget) const {
  auto meta_object = widget ? widget->metaObject() : nullptr;
  while (meta_object) {
    const auto type_id = meta_object->metaType().id();
    auto found_strategy = m_strategies.find(type_id);
    if (found_strategy != m_strategies.end()) {
      return found_strategy.value();
    }

    meta_object = meta_object->superClass();
  }

  return nullptr;
}

}  // namespace aegis
