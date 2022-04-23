/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

namespace flow::settings
{

  SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {}

  SettingsWidget::~SettingsWidget() = default;

  bool SettingsWidget::apply() { return true; }

  bool SettingsWidget::applied() const { return true; }

}// namespace flow::settings
