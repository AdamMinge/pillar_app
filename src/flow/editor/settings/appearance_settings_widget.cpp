/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/appearance_settings_widget.h"
/* -------------------------------------------------------------------------- */

AppearanceSettingsWidget::AppearanceSettingsWidget(QWidget *parent) : QWidget(parent)
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

void AppearanceSettingsWidget::initUi() {}

void AppearanceSettingsWidget::initConnections() {}

void AppearanceSettingsWidget::retranslateUi() {}
