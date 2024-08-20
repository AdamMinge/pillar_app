#ifndef AEGIS_RECORDER_RECORD_STRATEGY_H
#define AEGIS_RECORDER_RECORD_STRATEGY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointer>
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------- RecordStrategy --------------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordStrategy : public QObject {
  Q_OBJECT

 public:
  explicit RecordStrategy(QObject *parent = nullptr);
  ~RecordStrategy() override;

  void setWidget(QWidget *widget);
  [[nodiscard]] QWidget *getWidget() const;

 Q_SIGNALS:
  void recorded(const QString &command);

 protected:
  virtual void installConnections(QWidget *widget);
  virtual void removeConnections(QWidget *widget);

 private:
  QPointer<QWidget> m_widget;
};

/* ---------------------------- RecordButtonStrategy ------------------------ */

class LIB_AEGIS_RECORDER_COMMAND_API RecordButtonStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordButtonStrategy(QObject *parent = nullptr);
  ~RecordButtonStrategy() override;

 protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

 private Q_SLOTS:
  void onPressed();
  void onClicked();
  void onToggled(bool checked);
};

/* --------------------------- RecordComboBoxStrategy ----------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordComboBoxStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordComboBoxStrategy(QObject *parent = nullptr);
  ~RecordComboBoxStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onCurrentIndexChanged(int index);
};

/* --------------------------- RecordSpinBoxStrategy ------------------------ */

class LIB_AEGIS_RECORDER_COMMAND_API RecordSpinBoxStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordSpinBoxStrategy(QObject *parent = nullptr);
  ~RecordSpinBoxStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onValueChanged(double value);
  void onValueChanged(int value);
};

/* ---------------------------- RecordSliderStrategy ------------------------ */

class LIB_AEGIS_RECORDER_COMMAND_API RecordSliderStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordSliderStrategy(QObject *parent = nullptr);
  ~RecordSliderStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onValueChanged(int value);
};

/* ---------------------------- RecordTabBarStrategy ------------------------ */

class LIB_AEGIS_RECORDER_COMMAND_API RecordTabBarStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordTabBarStrategy(QObject *parent = nullptr);
  ~RecordTabBarStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;
  void removeConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onCurrentChanged(int index);
  void onTabClosed(int index);
  void onTabMoved(int from, int to);

 private:
  bool m_closing;
};

/* ---------------------------- RecordToolBoxStrategy ----------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordToolBoxStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordToolBoxStrategy(QObject *parent = nullptr);
  ~RecordToolBoxStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onCurrentChanged(int index);
};

/* ----------------------------- RecordMenuStrategy ------------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordMenuStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordMenuStrategy(QObject *parent = nullptr);
  ~RecordMenuStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onTriggered(QAction *action);
};

/* ---------------------------- RecordMenuBarStrategy ----------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordMenuBarStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordMenuBarStrategy(QObject *parent = nullptr);
  ~RecordMenuBarStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;
};

/* --------------------------- RecordTextEditStrategy ----------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordTextEditStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordTextEditStrategy(QObject *parent = nullptr);
  ~RecordTextEditStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onTextChanged();
};

/* --------------------------- RecordLineEditStrategy ----------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordLineEditStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordLineEditStrategy(QObject *parent = nullptr);
  ~RecordLineEditStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;
  bool eventFilter(QObject *obj, QEvent *event) override;

 private Q_SLOTS:
  void onTextChanged(const QString &text);
  void onReturnPressed();
};

/* --------------------------- RecordItemViewStrategy ----------------------- */

class LIB_AEGIS_RECORDER_COMMAND_API RecordItemViewStrategy
    : public RecordStrategy {
  Q_OBJECT

 public:
  static const int type;

 public:
  explicit RecordItemViewStrategy(QObject *parent = nullptr);
  ~RecordItemViewStrategy() override;

 protected:
  void installConnections(QWidget *widget) override;

 private Q_SLOTS:
  void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QList<int> &roles);
};

}  // namespace aegis

#endif  // AEGIS_RECORDER_RECORD_STRATEGY_H