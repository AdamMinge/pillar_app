#ifndef SETTINGS_WIDGET_TREE_MODEL_H
#define SETTINGS_WIDGET_TREE_MODEL_H

/* ---------------------------------- Standard ------------------------------ */
#include <map>
#include <set>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace egnite {
class SettingsWidgetFactory;
class SettingsWidget;
}  // namespace egnite

class SettingsWidgetTreeModel
    : public qtils::QtStackedWidgetTreeModel,
      public egnite::PluginListener<egnite::SettingsWidgetFactory> {
  Q_OBJECT

 public:
  explicit SettingsWidgetTreeModel(QObject *parent = nullptr);
  ~SettingsWidgetTreeModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;

 Q_SIGNALS:
  void appliedChanged(bool applied);

 protected:
  void addedObject(egnite::SettingsWidgetFactory *factory) override;
  void removedObject(egnite::SettingsWidgetFactory *factory) override;

 private Q_SLOTS:
  void onAppliedChanged(egnite::SettingsWidget *settings_widget, bool applied);

 private:
  QSet<egnite::SettingsWidget *> m_to_apply;
  QMap<egnite::SettingsWidgetFactory *, egnite::SettingsWidget *>
      m_settings_widget_by_factory;
};

#endif  // SETTINGS_WIDGET_TREE_MODEL_H
