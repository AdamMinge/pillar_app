/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings_dialog.h"
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/stacked_widget/stacked_widget_tree_model.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::SettingsDialog())
{
  initUi();
  initConnections();

  retranslateUi();
}

SettingsDialog::~SettingsDialog() = default;

void SettingsDialog::changeEvent(QEvent *event)
{
  QDialog::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void SettingsDialog::initUi()
{
  m_ui->setupUi(this);

  auto model = new utils::QtStackedWidgetTreeModel({}, this);
  m_ui->m_setting_list_view->setModel(model);

  m_ui->m_setting_widgets->setView(m_ui->m_setting_list_view);
}

void SettingsDialog::initConnections()
{

}

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Settings"));
}