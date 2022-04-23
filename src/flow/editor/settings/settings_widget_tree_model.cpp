/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget_tree_model.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/settings/settings_widget.h>
#include <flow/libflow/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

SettingsWidgetTreeModel::SettingsWidgetTreeModel(QObject *parent)
    : utils::QtStackedWidgetTreeModel(parent)
{
  init();
}

SettingsWidgetTreeModel::~SettingsWidgetTreeModel() = default;

bool SettingsWidgetTreeModel::apply()
{
  std::set<flow::settings::SettingsWidget *> applied_widget;

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

void SettingsWidgetTreeModel::addedObject(
  flow::settings::SettingsWidgetFactory *factory)
{
  auto parent_index = QModelIndex{};
  if (auto parent_name = factory->getParentObjectName(); !parent_name.isEmpty())
    parent_index = getIndexBy(Role::ObjectNameRole, parent_name, QModelIndex{});

  auto settings_widget = factory->create().release();
  m_settings_widget_by_factory[factory].push_back(settings_widget);

  append(new utils::QtStackedWidgetTreeItem(settings_widget), parent_index);

  connect(
    settings_widget, &flow::settings::SettingsWidget::appliedChanged, this,
    [this, settings_widget](auto applied) {
      onAppliedChanged(settings_widget, applied);
    });
}

void SettingsWidgetTreeModel::removedObject(
  flow::settings::SettingsWidgetFactory *factory)
{
  for (auto settings_widget : m_settings_widget_by_factory[factory])
  {
    auto index = getIndexBy(
      Role::WidgetRole, QVariant::fromValue(settings_widget), QModelIndex{});
    remove(index);
  }
}

void SettingsWidgetTreeModel::init()
{
  auto settings_widgets = getObjects();
  for (auto settings_widget : settings_widgets) addedObject(settings_widget);
}

void SettingsWidgetTreeModel::onAppliedChanged(
  flow::settings::SettingsWidget *settings_widget, bool applied)
{
  if (!applied) m_to_apply.insert(settings_widget);
  else if (m_to_apply.contains(settings_widget))
    m_to_apply.erase(settings_widget);

  Q_EMIT appliedChanged(m_to_apply.empty());
}
