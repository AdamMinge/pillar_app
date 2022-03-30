#ifndef FLOW_SETTINGS_WIDGET_TREE_MODEL_H
#define FLOW_SETTINGS_WIDGET_TREE_MODEL_H

/* ---------------------------------- Standard ------------------------------ */
#include <set>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

class SettingsWidget;

class SettingsWidgetTreeModel : public utils::QtStackedWidgetTreeModel
{
  Q_OBJECT

public:
  explicit SettingsWidgetTreeModel(
    const QList<utils::QtStackedWidgetTreeItem *> &root_items,
    QObject *parent = nullptr);
  ~SettingsWidgetTreeModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;

Q_SIGNALS:
  void appliedChanged(bool applied);

private Q_SLOTS:
  void onAppliedChanged(SettingsWidget *settings_widget, bool applied);

private:
  void connectOnAppliedChanged(const QModelIndex &parent);

private:
  std::set<SettingsWidget *> m_to_apply;
};

#endif//FLOW_SETTINGS_WIDGET_TREE_MODEL_H
