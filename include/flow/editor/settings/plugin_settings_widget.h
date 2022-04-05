#ifndef FLOW_PLUGIN_SETTINGS_WIDGET_H
#define FLOW_PLUGIN_SETTINGS_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class PluginSettingsWidget;
}

class PluginListModel;
class PluginListDelegate;

class PluginSettingsWidget : public SettingsWidget
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

#endif//FLOW_PLUGIN_SETTINGS_WIDGET_H
