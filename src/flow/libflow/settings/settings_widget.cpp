/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/settings/settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* -------------------------------------------------------------------------- */

namespace flow {

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {}

SettingsWidget::~SettingsWidget() = default;

bool SettingsWidget::apply() { return true; }

bool SettingsWidget::applied() const { return true; }

}  // namespace flow
