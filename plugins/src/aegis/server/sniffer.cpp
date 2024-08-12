/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/sniffer.h"

#include "aegis/server/searcher/searcher_manager.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/dpi/dpi.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCursor>
#include <QMouseEvent>
#include <QPainter>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- SnifferObjectTooltip ------------------------ */

SnifferObjectTooltip::SnifferObjectTooltip(QWidget *parent)
    : QDialog(parent), m_object(nullptr) {
  initUi();
}

SnifferObjectTooltip::~SnifferObjectTooltip() {}

QObject *SnifferObjectTooltip::getObject() const { return m_object; }

void SnifferObjectTooltip::setObject(QObject *object) {
  if (m_object != object) {
    m_object = object;

    if (m_object) {
      const auto id =
          m_object ? SearcherManager::getInstance().getId(m_object) : "";
      m_label->setText(id);
      show();
    } else {
      hide();
    }
  }
}

void SnifferObjectTooltip::initUi() {
  setWindowFlags(Qt::ToolTip);
  setAttribute(Qt::WA_TranslucentBackground);
  setStyleSheet(
      "QDialog { background-color: rgba(255, 255, 224, 230); border: 1px solid "
      "gray; border-radius: 5px; }");

  auto layout = new QVBoxLayout(this);
  m_label = new QLabel(this);
  m_label->setWordWrap(true);
  m_label->setAlignment(Qt::AlignLeft);
  layout->addWidget(m_label);
  layout->setContentsMargins(8, 8, 8, 8);
}

/* ----------------------------- SnifferWidgetMarker ------------------------ */

SnifferWidgetMarker::SnifferWidgetMarker(QWidget *parent)
    : QLabel(parent), m_widget(nullptr) {
  setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint |
                 Qt::WindowTransparentForInput | Qt::WindowDoesNotAcceptFocus |
                 Qt::WindowStaysOnTopHint | Qt::ToolTip);

  setAttribute(Qt::WA_TranslucentBackground);
  setAttribute(Qt::WA_TransparentForMouseEvents);
}

SnifferWidgetMarker::~SnifferWidgetMarker() = default;

QWidget *SnifferWidgetMarker::getWidget() const { return m_widget; }

void SnifferWidgetMarker::setWidget(QWidget *widget) {
  if (m_widget != widget) {
    m_widget = widget;

    if (m_widget) {
      resize(m_widget->size());
      move(m_widget->mapToGlobal(QPoint(0, 0)));
      show();
      raise();
    } else {
      hide();
    }
  }
}

void SnifferWidgetMarker::paintEvent(QPaintEvent *event) {
  if (!m_widget) return;

  auto painter = QPainter(this);
  auto pen = QPen(Qt::red, 2);

  painter.setPen(pen);
  painter.drawRect(rect().adjusted(1, 1, -2, -2));
}

/* ---------------------------------- Sniffer ------------------------------- */

Sniffer::Sniffer(QObject *parent) : QObject(parent), m_sniffing(false) {}

Sniffer::~Sniffer() = default;

void Sniffer::start() {
  if (!m_sniffing) {
    m_sniffing = true;

    qApp->installEventFilter(this);

    m_tooltip.reset(new SnifferObjectTooltip);
    m_marker.reset(new SnifferWidgetMarker);
  }
}

void Sniffer::stop() {
  if (m_sniffing) {
    m_sniffing = false;

    qApp->removeEventFilter(this);

    m_tooltip.reset(nullptr);
    m_marker.reset(nullptr);
  }
}

bool Sniffer::isSniffing() { return m_sniffing; }

bool Sniffer::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::MouseMove) {
    onMouseMove(static_cast<QMouseEvent *>(event));
  }

  return QObject::eventFilter(obj, event);
}

void Sniffer::onMouseMove(QMouseEvent *event) {
  const auto global_pos = event->globalPosition().toPoint();
  const auto widget = qApp->widgetAt(global_pos);

  m_tooltip->move(global_pos + qtils::dpiScaled(QPoint(10, 10)));
  m_tooltip->setObject(widget);
  m_marker->setWidget(widget);
}

}  // namespace aegis