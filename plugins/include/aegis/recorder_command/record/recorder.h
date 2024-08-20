#ifndef AEGIS_RECORDER_RECORD_RECORDER_H
#define AEGIS_RECORDER_RECORD_RECORDER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QThread>
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class RecordStrategy;

/* ------------------------------- WidgetListener --------------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API WidgetListener : public QObject {
  Q_OBJECT

 public:
  explicit WidgetListener(QObject *parent = nullptr);
  ~WidgetListener() override;

 Q_SIGNALS:
  void currentWidgetChanged(QWidget *widget);

 protected Q_SLOTS:
  bool eventFilter(QObject *obj, QEvent *event) override;

 private:
  void setWidget(QWidget *widget);
  [[nodiscard]] QWidget *findWidget(QWidget *widget) const;

 private:
  QWidget *m_current_widget;
};

/* ---------------------------------- Recorder ------------------------------ */

class LIB_AEGIS_RECORDER_COMMAND_API Recorder : public QObject {
  Q_OBJECT

 public:
  explicit Recorder(QObject *parent = nullptr);
  ~Recorder() override;

  void start();
  void stop();
  void clear();

  [[nodiscard]] const QStringList &getReport() const;

 protected Q_SLOTS:
  void onCurrentWidgetChanged(QWidget *widget);
  void onRecorder(const QString &command);

 private:
  [[nodiscard]] RecordStrategy *findStrategy(QWidget *widget) const;

 private:
  QMap<int, RecordStrategy *> m_strategies;
  RecordStrategy *m_current_strategy;
  WidgetListener *m_widget_listener;
  QStringList m_report;
  bool m_running;
};

}  // namespace aegis

#endif  // AEGIS_RECORDER_RECORD_RECORDER_H