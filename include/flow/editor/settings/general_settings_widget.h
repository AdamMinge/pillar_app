#ifndef FLOW_GENERAL_SETTINGS_WIDGET_H
#define FLOW_GENERAL_SETTINGS_WIDGET_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/settings/settings_widget.h>
#include <flow/libflow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class GeneralSettingsWidget;
}

class GeneralSettingsWidget : public flow::settings::SettingsWidget
{
  Q_OBJECT

public:
  explicit GeneralSettingsWidget(QWidget *parent = nullptr);
  ~GeneralSettingsWidget() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::GeneralSettingsWidget> m_ui;
};

class GeneralSettingsWidgetFactory
    : public flow::settings::SettingsWidgetFactory
{
  Q_OBJECT
  Q_INTERFACES(flow::settings::SettingsWidgetFactory)

public:
  explicit GeneralSettingsWidgetFactory(QObject *parent = nullptr);
  ~GeneralSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::settings::SettingsWidget>
  create() const override;
};

#endif//FLOW_GENERAL_SETTINGS_WIDGET_H
