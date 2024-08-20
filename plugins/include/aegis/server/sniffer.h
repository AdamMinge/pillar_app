#ifndef AEGIS_SERVER_SNIFFER_SNIFFER_H
#define AEGIS_SERVER_SNIFFER_SNIFFER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
#include <QLabel>
#include <QObject>
#include <QTimer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- SnifferObjectTooltip ------------------------ */

class SnifferObjectTooltip : public QDialog {
  Q_OBJECT

 public:
  explicit SnifferObjectTooltip(QWidget *parent = nullptr);
  ~SnifferObjectTooltip() override;

  [[nodiscard]] QObject *getObject() const;
  void setObject(QObject *object);

 private:
  void initUi();

 private:
  QLabel *m_label;
  QObject *m_object;
};

/* ----------------------------- SnifferWidgetMarker ------------------------ */

class SnifferWidgetMarker : public QLabel {
  Q_OBJECT

 public:
  explicit SnifferWidgetMarker(QWidget *parent = nullptr);
  ~SnifferWidgetMarker() override;

  [[nodiscard]] QWidget *getWidget() const;
  void setWidget(QWidget *widget);

  [[nodiscard]] QColor getColor() const;
  void setColor(QColor color);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  QWidget *m_widget;
  QColor m_color;
};

/* ---------------------------------- Sniffer ------------------------------- */

class SnifferPrivate;

class Sniffer : public QObject {
  Q_OBJECT

 public:
  Sniffer(QObject *parent = nullptr);
  ~Sniffer() override;

  void start();
  void stop();

  [[nodiscard]] bool isSniffing();

  [[nodiscard]] QColor getMarkerColor() const;
  void setMarkerColor(QColor color);

 protected Q_SLOTS:
  bool eventFilter(QObject *obj, QEvent *event) override;
  void onMouseMove(QMouseEvent *event);

 private:
  bool m_sniffing;
  QScopedPointer<SnifferObjectTooltip> m_tooltip;
  QScopedPointer<SnifferWidgetMarker> m_marker;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SNIFFER_SNIFFER_H