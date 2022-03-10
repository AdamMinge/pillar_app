/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/general_settings_widget.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_general_settings_widget.h"
/* -------------------------------------------------------------------------- */

GeneralSettingsWidget::GeneralSettingsWidget(QWidget *parent)
    : SettingsWidget(parent), m_ui(new Ui::GeneralSettingsWidget())
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

void GeneralSettingsWidget::initUi() { m_ui->setupUi(this); }

void GeneralSettingsWidget::initConnections() {}

void GeneralSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }
