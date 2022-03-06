/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/plugin_settings_widget.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_plugin_settings_widget.h"
/* -------------------------------------------------------------------------- */

PluginSettingsWidget::PluginSettingsWidget(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::PluginSettingsWidget())
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

void PluginSettingsWidget::initUi() { m_ui->setupUi(this); }

void PluginSettingsWidget::initConnections() {}

void PluginSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }
