#ifndef FLOW_GENERAL_SETTINGS_WIDGET_H
#define FLOW_GENERAL_SETTINGS_WIDGET_H

/* ----------------------------------- Flow --------------------------------- */
#include <flow/settings/settings_widget.h>
#include <flow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class GeneralSettingsWidget;
}

class GeneralSettingsWidget : public flow::SettingsWidget {
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

class GeneralSettingsWidgetFactory : public flow::SettingsWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::SettingsWidgetFactory)

 public:
  explicit GeneralSettingsWidgetFactory(QObject *parent = nullptr);
  ~GeneralSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::SettingsWidget> create() const override;
};

#endif  // FLOW_GENERAL_SETTINGS_WIDGET_H
