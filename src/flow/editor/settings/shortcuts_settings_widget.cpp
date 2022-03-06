/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_settings_widget.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_shortcuts_settings_widget.h"
/* -------------------------------------------------------------------------- */

ShortcutsSettingsWidget::ShortcutsSettingsWidget(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::ShortcutsSettingsWidget())
{
  initUi();
  initConnections();

  retranslateUi();
}

ShortcutsSettingsWidget::~ShortcutsSettingsWidget() = default;

void ShortcutsSettingsWidget::changeEvent(QEvent *event)
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

void ShortcutsSettingsWidget::initUi() { m_ui->setupUi(this); }

void ShortcutsSettingsWidget::initConnections() {}

void ShortcutsSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }
