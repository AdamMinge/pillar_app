/* ----------------------------------- Local -------------------------------- */
#include "egnite/settings/settings_widget_factory.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

SettingsWidgetFactory::SettingsWidgetFactory(QObject *parent)
    : QObject(parent) {}

SettingsWidgetFactory::~SettingsWidgetFactory() = default;

QString SettingsWidgetFactory::getParentObjectName() const {
  return QLatin1String{};
}

}  // namespace egnite
