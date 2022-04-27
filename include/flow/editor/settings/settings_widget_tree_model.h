#ifndef FLOW_SETTINGS_WIDGET_TREE_MODEL_H
#define FLOW_SETTINGS_WIDGET_TREE_MODEL_H

/* ---------------------------------- Standard ------------------------------ */
#include <map>
#include <set>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_listener.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace flow::settings
{
  class SettingsWidgetFactory;
  class SettingsWidget;
}// namespace flow::settings

class SettingsWidgetTreeModel
    : public utils::QtStackedWidgetTreeModel,
      public flow::PluginListener<flow::settings::SettingsWidgetFactory>
{
  Q_OBJECT

public:
  explicit SettingsWidgetTreeModel(QObject *parent = nullptr);
  ~SettingsWidgetTreeModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;

Q_SIGNALS:
  void appliedChanged(bool applied);

protected:
  void addedObject(flow::settings::SettingsWidgetFactory *factory) override;
  void removedObject(flow::settings::SettingsWidgetFactory *factory) override;

private Q_SLOTS:
  void onAppliedChanged(
    flow::settings::SettingsWidget *settings_widget, bool applied);

private:
  std::set<flow::settings::SettingsWidget *> m_to_apply;
  std::map<
    flow::settings::SettingsWidgetFactory *, flow::settings::SettingsWidget *>
    m_settings_widget_by_factory;
};

#endif//FLOW_SETTINGS_WIDGET_TREE_MODEL_H
