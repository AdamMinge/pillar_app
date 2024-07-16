#ifndef PILLAR_SETTINGS_WIDGET_H
#define PILLAR_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace pillar {

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

}  // namespace pillar

#endif  // PILLAR_SETTINGS_WIDGET_H
