/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/appearance_settings_widget.h"
#include "flow/editor/settings/plugin_settings_widget.h"
#include "flow/editor/settings/settings_dialog.h"
#include "flow/editor/settings/shortcuts_settings_widget.h"
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

void SettingsDialog::filterSettings(const QString &filter)
{
  auto filter_model =
    qobject_cast<QSortFilterProxyModel *>(m_ui->m_setting_list_view->model());
  filter_model->setFilterWildcard(filter);
}

void SettingsDialog::initUi()
{
  m_ui->setupUi(this);

  m_ui->m_setting_list_view->setModel(createStackedWidgetTreeModel());
  m_ui->m_setting_widgets->setView(m_ui->m_setting_list_view);
}

void SettingsDialog::initConnections()
{
  connect(
    m_ui->m_setting_search, &QLineEdit::textChanged, this,
    &SettingsDialog::filterSettings);
}

QAbstractItemModel *SettingsDialog::createStackedWidgetTreeModel()
{
  auto settings_root = {
    new utils::QtStackedWidgetTreeItem(
      "General", nullptr,
      {new utils::QtStackedWidgetTreeItem(
        "Appearance", new AppearanceSettingsWidget(this))}),
    new utils::QtStackedWidgetTreeItem(
      "Shortcuts", new ShortcutsSettingsWidget(this)),
    new utils::QtStackedWidgetTreeItem(
      "Plugins", new PluginSettingsWidget(this))};

  auto filter_model = new QSortFilterProxyModel(this);
  filter_model->setRecursiveFilteringEnabled(true);

  filter_model->setSourceModel(
    new utils::QtStackedWidgetTreeModel(settings_root, filter_model));

  return filter_model;
}

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Settings"));
}