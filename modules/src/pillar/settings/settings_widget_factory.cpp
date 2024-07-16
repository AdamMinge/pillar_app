/* ----------------------------------- Local -------------------------------- */
#include "pillar/settings/settings_widget_factory.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

SettingsWidgetFactory::SettingsWidgetFactory(QObject *parent)
    : QObject(parent) {}

SettingsWidgetFactory::~SettingsWidgetFactory() = default;

QString SettingsWidgetFactory::getParentObjectName() const {
  return QLatin1String{};
}

}  // namespace pillar
