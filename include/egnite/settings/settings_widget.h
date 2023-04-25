#ifndef EGNITE_SETTINGS_WIDGET_H
#define EGNITE_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace egnite {

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

}  // namespace egnite

#endif  // EGNITE_SETTINGS_WIDGET_H
