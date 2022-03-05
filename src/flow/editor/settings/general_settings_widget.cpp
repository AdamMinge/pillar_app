/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/general_settings_widget.h"
/* -------------------------------------------------------------------------- */

GeneralSettingsWidget::GeneralSettingsWidget(QWidget *parent) : QWidget(parent)
{
  initUi();
  initConnections();

  retranslateUi();
}

GeneralSettingsWidget::~GeneralSettingsWidget() = default;

void GeneralSettingsWidget::changeEvent(QEvent *event)
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

void GeneralSettingsWidget::initUi() {}

void GeneralSettingsWidget::initConnections() {}

void GeneralSettingsWidget::retranslateUi() {}
