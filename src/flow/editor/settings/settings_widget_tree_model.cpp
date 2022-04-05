/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget_tree_model.h"
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

SettingsWidgetTreeModel::SettingsWidgetTreeModel(
  const QList<utils::QtStackedWidgetTreeItem *> &root_items, QObject *parent)
    : utils::QtStackedWidgetTreeModel(root_items, parent)
{
  connectOnAppliedChanged(QModelIndex{});
}

SettingsWidgetTreeModel::~SettingsWidgetTreeModel() = default;

bool SettingsWidgetTreeModel::apply()
{
  std::set<SettingsWidget *> applied_widget;

  std::for_each(
    m_to_apply.begin(), m_to_apply.end(),
    [&applied_widget](auto settings_widget) {
      if (settings_widget->apply()) applied_widget.insert(settings_widget);
    });

  std::for_each(
    applied_widget.begin(), applied_widget.end(),
    [this](auto settings_widget) { onAppliedChanged(settings_widget, true); });

  return applied();
}

bool SettingsWidgetTreeModel::applied() const { return m_to_apply.empty(); }

void SettingsWidgetTreeModel::onAppliedChanged(
  SettingsWidget *settings_widget, bool applied)
{
  if (!applied) m_to_apply.insert(settings_widget);
  else if (m_to_apply.contains(settings_widget))
    m_to_apply.erase(settings_widget);

  Q_EMIT appliedChanged(m_to_apply.empty());
}

void SettingsWidgetTreeModel::connectOnAppliedChanged(const QModelIndex &parent)
{
  for (auto row = 0; row < rowCount(parent); ++row)
  {
    const auto current_index = index(row, 0, parent);
    const auto current_widget =
      data(current_index, Role::WidgetRole).value<QWidget *>();

    if (auto settings_widget = qobject_cast<SettingsWidget *>(current_widget);
        settings_widget)
    {
      connect(
        settings_widget, &SettingsWidget::appliedChanged, this,
        [this, settings_widget](auto applied) {
          onAppliedChanged(settings_widget, applied);
        });
    }

    connectOnAppliedChanged(current_index);
  }
}