/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/settings_widget.h"
/* -------------------------------------------------------------------------- */

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {}

SettingsWidget::~SettingsWidget() = default;

void SettingsWidget::apply() {}

bool SettingsWidget::applied() const { return true; }
