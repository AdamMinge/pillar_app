/* ----------------------------------- Local -------------------------------- */
#include "settings/settings_widget_tree_model.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/settings/settings_widget.h>
#include <pillar/settings/settings_widget_factory.h>
/* -------------------------------------------------------------------------- */

SettingsWidgetTreeModel::SettingsWidgetTreeModel(QObject *parent)
    : qtils::QtStackedWidgetTreeModel(parent) {
  loadObjects();
}

SettingsWidgetTreeModel::~SettingsWidgetTreeModel() {
  qDeleteAll(m_settings_widget_by_factory);
}

bool SettingsWidgetTreeModel::apply() {
  const auto to_apply = m_to_apply;
  QSet<pillar::SettingsWidget *> applied_widget;

  std::for_each(to_apply.begin(), to_apply.end(),
                [&applied_widget](auto settings_widget) {
                  if (settings_widget->apply())
                    applied_widget.insert(settings_widget);
                });

  std::for_each(applied_widget.begin(), applied_widget.end(),
                [this](auto settings_widget) {
                  onAppliedChanged(settings_widget, true);
                });

  return applied();
}

bool SettingsWidgetTreeModel::applied() const { return m_to_apply.empty(); }

void SettingsWidgetTreeModel::addedObject(
    pillar::SettingsWidgetFactory *factory) {
  auto parent_index = QModelIndex{};
  if (auto parent_name = factory->getParentObjectName(); !parent_name.isEmpty())
    parent_index = getIndexBy(Role::ObjectNameRole, parent_name, QModelIndex{});

  auto settings_widget = factory->create().release();
  m_settings_widget_by_factory[factory] = settings_widget;

  append(new qtils::QtStackedWidgetTreeItem(settings_widget), parent_index);

  connect(settings_widget, &pillar::SettingsWidget::appliedChanged, this,
          [this, settings_widget](auto applied) {
            onAppliedChanged(settings_widget, applied);
          });
}

void SettingsWidgetTreeModel::removedObject(
    pillar::SettingsWidgetFactory *factory) {
  if (m_settings_widget_by_factory.contains(factory)) {
    auto settings_widget = m_settings_widget_by_factory.take(factory);
    auto index = getIndexBy(
        Role::WidgetRole, QVariant::fromValue(settings_widget), QModelIndex{});

    settings_widget->deleteLater();
    remove(index);
  }
}

void SettingsWidgetTreeModel::onAppliedChanged(
    pillar::SettingsWidget *settings_widget, bool applied) {
  if (!applied)
    m_to_apply.insert(settings_widget);
  else if (m_to_apply.contains(settings_widget))
    m_to_apply.remove(settings_widget);

  Q_EMIT appliedChanged(m_to_apply.empty());
}
