#ifndef FLOW_SHORTCUTS_SETTINGS_WIDGET_H
#define FLOW_SHORTCUTS_SETTINGS_WIDGET_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class ShortcutsSettingsWidget;
}

class ShortcutsSettingsWidget : public SettingsWidget
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

private:
  QScopedPointer<Ui::ShortcutsSettingsWidget> m_ui;
};

#endif//FLOW_SHORTCUTS_SETTINGS_WIDGET_H
