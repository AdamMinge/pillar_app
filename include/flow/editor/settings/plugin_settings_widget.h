#ifndef FLOW_PLUGIN_SETTINGS_WIDGET_H
#define FLOW_PLUGIN_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

class PluginSettingsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PluginSettingsWidget(QWidget* parent = nullptr);
  ~PluginSettingsWidget() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();
};

#endif//FLOW_PLUGIN_SETTINGS_WIDGET_H
