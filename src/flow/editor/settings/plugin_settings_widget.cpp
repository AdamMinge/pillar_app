/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/plugin_settings_widget.h"
/* -------------------------------------------------------------------------- */

PluginSettingsWidget::PluginSettingsWidget(QWidget *parent) : QWidget(parent)
{
  initUi();
  initConnections();

  retranslateUi();
}

PluginSettingsWidget::~PluginSettingsWidget() = default;

void PluginSettingsWidget::changeEvent(QEvent *event)
{
  QWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void PluginSettingsWidget::initUi() {}

void PluginSettingsWidget::initConnections() {}

void PluginSettingsWidget::retranslateUi() {}
