#ifndef FLOW_SHORTCUTS_SETTINGS_WIDGET_H
#define FLOW_SHORTCUTS_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class ShortcutsSettingsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ShortcutsSettingsWidget(QWidget *parent = nullptr);
  ~ShortcutsSettingsWidget() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();
};

#endif//FLOW_SHORTCUTS_SETTINGS_WIDGET_H
