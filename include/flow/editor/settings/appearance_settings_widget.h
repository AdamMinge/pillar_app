#ifndef FLOW_APPEARANCE_SETTINGS_WIDGET_H
#define FLOW_APPEARANCE_SETTINGS_WIDGET_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class AppearanceSettingsWidget;
}

class AppearanceSettingsWidget : public SettingsWidget
{
  Q_OBJECT

public:
  explicit AppearanceSettingsWidget(QWidget *parent = nullptr);
  ~AppearanceSettingsWidget() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::AppearanceSettingsWidget> m_ui;
};

#endif//FLOW_APPEARANCE_SETTINGS_WIDGET_H
