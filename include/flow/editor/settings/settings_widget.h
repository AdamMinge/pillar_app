#ifndef FLOW_SETTINGS_WIDGET_H
#define FLOW_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class SettingsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit SettingsWidget(QWidget *parent = nullptr);
  ~SettingsWidget() override;

  virtual void apply();
  [[nodiscard]] virtual bool applied() const;

Q_SIGNALS:
  void appliedChanged(bool applied);
};

#endif//FLOW_SETTINGS_WIDGET_H
