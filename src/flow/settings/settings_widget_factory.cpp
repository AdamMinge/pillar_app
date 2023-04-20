/* ----------------------------------- Local -------------------------------- */
#include "flow/settings/settings_widget_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

SettingsWidgetFactory::SettingsWidgetFactory(QObject *parent)
    : QObject(parent) {}

SettingsWidgetFactory::~SettingsWidgetFactory() = default;

QString SettingsWidgetFactory::getParentObjectName() const {
  return QLatin1String{};
}

}  // namespace flow
