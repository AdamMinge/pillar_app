/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_settings_widget.h"
/* -------------------------------------------------------------------------- */

ShortcutsSettingsWidget::ShortcutsSettingsWidget(QWidget *parent)
    : QWidget(parent)
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

void ShortcutsSettingsWidget::initUi() {}

void ShortcutsSettingsWidget::initConnections() {}

void ShortcutsSettingsWidget::retranslateUi() {}
