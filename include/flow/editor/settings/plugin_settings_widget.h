#ifndef FLOW_PLUGIN_SETTINGS_WIDGET_H
#define FLOW_PLUGIN_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class PluginSettingsWidget;
}

class PluginSettingsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PluginSettingsWidget(QWidget *parent = nullptr);
  ~PluginSettingsWidget() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::PluginSettingsWidget> m_ui;
};

#endif//FLOW_PLUGIN_SETTINGS_WIDGET_H
