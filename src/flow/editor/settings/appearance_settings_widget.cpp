/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/appearance_settings_widget.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_appearance_settings_widget.h"
/* -------------------------------------------------------------------------- */

AppearanceSettingsWidget::AppearanceSettingsWidget(QWidget *parent)
    : SettingsWidget(parent), m_ui(new Ui::AppearanceSettingsWidget())
{
  initUi();
  initConnections();

  retranslateUi();
}

AppearanceSettingsWidget::~AppearanceSettingsWidget() = default;

void AppearanceSettingsWidget::changeEvent(QEvent *event)
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

void AppearanceSettingsWidget::initUi() { m_ui->setupUi(this); }

void AppearanceSettingsWidget::initConnections() {}

void AppearanceSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }
