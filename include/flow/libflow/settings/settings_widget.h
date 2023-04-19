#ifndef FLOW_SETTINGS_WIDGET_H
#define FLOW_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace flow {

class SettingsWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget *parent = nullptr);
  ~SettingsWidget() override;

  virtual bool apply();
  [[nodiscard]] virtual bool applied() const;

 Q_SIGNALS:
  void appliedChanged(bool applied);

 private:
  QString m_parent_name;
};

}  // namespace flow

#endif  // FLOW_SETTINGS_WIDGET_H
