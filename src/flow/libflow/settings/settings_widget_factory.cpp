/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/settings/settings_widget_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow::settings
{
  SettingsWidgetFactory::SettingsWidgetFactory(QObject *parent)
      : QObject(parent)
  {}

  SettingsWidgetFactory::~SettingsWidgetFactory() = default;

  QString SettingsWidgetFactory::getParentObjectName() const
  {
    return QLatin1String{};
  }
}// namespace flow::settings
