/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {}

SettingsWidget::~SettingsWidget() = default;

bool SettingsWidget::apply() { return true; }

bool SettingsWidget::applied() const { return true; }
