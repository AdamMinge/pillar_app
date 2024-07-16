#ifndef SETTINGS_WIDGET_TREE_MODEL_H
#define SETTINGS_WIDGET_TREE_MODEL_H

/* ---------------------------------- Standard ------------------------------ */
#include <map>
#include <set>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_listener.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace pillar {
class SettingsWidgetFactory;
class SettingsWidget;
}  // namespace pillar

class SettingsWidgetTreeModel
    : public qtils::QtStackedWidgetTreeModel,
      public pillar::PluginListener<pillar::SettingsWidgetFactory> {
  Q_OBJECT

 public:
  explicit SettingsWidgetTreeModel(QObject *parent = nullptr);
  ~SettingsWidgetTreeModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;

 Q_SIGNALS:
  void appliedChanged(bool applied);

 protected:
  void addedObject(pillar::SettingsWidgetFactory *factory) override;
  void removedObject(pillar::SettingsWidgetFactory *factory) override;

 private Q_SLOTS:
  void onAppliedChanged(pillar::SettingsWidget *settings_widget, bool applied);

 private:
  QSet<pillar::SettingsWidget *> m_to_apply;
  QMap<pillar::SettingsWidgetFactory *, pillar::SettingsWidget *>
      m_settings_widget_by_factory;
};

#endif  // SETTINGS_WIDGET_TREE_MODEL_H
