#ifndef PLUGIN_SETTINGS_WIDGET_H
#define PLUGIN_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/settings/settings_widget.h>
#include <pillar/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class PluginSettingsWidget;
}

class PluginListModel;
class PluginListDelegate;

class PluginSettingsWidget : public pillar::SettingsWidget {
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
  void checkAvailability();

 private:
  QScopedPointer<Ui::PluginSettingsWidget> m_ui;

  QScopedPointer<PluginListModel> m_plugin_list_model;
  QScopedPointer<PluginListDelegate> m_plugin_list_delegate;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

class PluginSettingsWidgetFactory : public pillar::SettingsWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(pillar::SettingsWidgetFactory)

 public:
  explicit PluginSettingsWidgetFactory(QObject *parent = nullptr);
  ~PluginSettingsWidgetFactory() override;

  [[nodiscard]] std::unique_ptr<pillar::SettingsWidget> create() const override;
};

#endif  // PLUGIN_SETTINGS_WIDGET_H
