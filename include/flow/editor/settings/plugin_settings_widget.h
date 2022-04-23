#ifndef FLOW_PLUGIN_SETTINGS_WIDGET_H
#define FLOW_PLUGIN_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/settings/settings_widget.h>
#include <flow/libflow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class PluginSettingsWidget;
}

class PluginListModel;
class PluginListDelegate;

class PluginSettingsWidget : public flow::settings::SettingsWidget
{
  Q_OBJECT

public:
  explicit PluginSettingsWidget(QWidget *parent = nullptr);
  ~PluginSettingsWidget() override;

  bool apply() override;
  [[nodiscard]] bool applied() const override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private Q_SLOTS:
  void searchPlugin(const QString &search);

private:
  QScopedPointer<Ui::PluginSettingsWidget> m_ui;

  QScopedPointer<PluginListModel> m_plugin_list_model;
  QScopedPointer<PluginListDelegate> m_plugin_list_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

class PluginSettingsWidgetFactory : public flow::settings::SettingsWidgetFactory
{
  Q_OBJECT
  Q_INTERFACES(flow::settings::SettingsWidgetFactory)

public:
  explicit PluginSettingsWidgetFactory(QObject *parent = nullptr);
  ~PluginSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<flow::settings::SettingsWidget>
  create() const override;
};

#endif//FLOW_PLUGIN_SETTINGS_WIDGET_H
