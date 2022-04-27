#ifndef FLOW_APPEARANCE_SETTINGS_WIDGET_H
#define FLOW_APPEARANCE_SETTINGS_WIDGET_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/settings/settings_widget.h>
#include <flow/libflow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class AppearanceSettingsWidget;
}

class AppearanceSettingsWidget : public flow::settings::SettingsWidget
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

private Q_SLOTS:
  void languageChanged(const QString &language);
  void styleChanged(const QString &style);

private:
  QScopedPointer<Ui::AppearanceSettingsWidget> m_ui;
};

class AppearanceSettingsWidgetFactory
    : public flow::settings::SettingsWidgetFactory
{
  Q_OBJECT
  Q_INTERFACES(flow::settings::SettingsWidgetFactory)

public:
  explicit AppearanceSettingsWidgetFactory(QObject *parent = nullptr);
  ~AppearanceSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::settings::SettingsWidget>
  create() const override;
  [[nodiscard]] QString getParentObjectName() const override;
};

#endif//FLOW_APPEARANCE_SETTINGS_WIDGET_H
