/* ------------------------------------ Qt ---------------------------------- */
#include <QDesktopServices>
#include <QLabel>
#include <QMessageBox>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/appearance_settings_widget.h"
#include "flow/editor/settings/general_settings_widget.h"
#include "flow/editor/settings/plugin_settings_widget.h"
#include "flow/editor/settings/settings_dialog.h"
#include "flow/editor/settings/settings_widget_tree_model.h"
#include "flow/editor/settings/shortcuts_settings_widget.h"
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/stacked_widget/stacked_widget_tree_delegate.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

namespace
{

  [[nodiscard]] SettingsWidgetTreeModel *
  getSourceModel(QAbstractItemModel *model)
  {
    auto filter_model = qobject_cast<QSortFilterProxyModel *>(model);
    auto settings_model =
      filter_model
        ? qobject_cast<SettingsWidgetTreeModel *>(filter_model->sourceModel())
        : nullptr;

    return settings_model;
  }

  [[nodiscard]] QSortFilterProxyModel *getFilterModel(QAbstractItemModel *model)
  {
    return qobject_cast<QSortFilterProxyModel *>(model);
  }

}// namespace

SettingsDialog::SettingsDialog(QWidget *parent)
    : utils::QtDialogWithUrlLinks<SettingsDialog>(parent),
      m_ui(new Ui::SettingsDialog())
{
  initUi();
  initConnections();

  SettingsDialog::setUrl(QUrl("settings:General"));

  retranslateUi();
}

SettingsDialog::~SettingsDialog() = default;

void SettingsDialog::setUrl(const QUrl &url)
{
  if (url.scheme() != QLatin1String("settings")) return;

  auto model = m_ui->m_setting_list_view->model();
  auto index = SettingsWidgetTreeModel::getIndexByName(
    *model, url.toString(QUrl::RemoveScheme), QModelIndex{});

  if(!index.isValid())
  {
    m_ui->m_setting_search->setText(QLatin1String{});

    index = SettingsWidgetTreeModel::getIndexByName(
      *model, url.toString(QUrl::RemoveScheme), QModelIndex{});
  }

  m_ui->m_setting_list_view->selectionModel()->select(
    index, QItemSelectionModel::ClearAndSelect);
}

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
  auto filter_model = getFilterModel(m_ui->m_setting_list_view->model());
  Q_ASSERT(filter_model);

  filter_model->setFilterWildcard(filter);
}

void SettingsDialog::ok()
{
  apply();
  cancel();
}

void SettingsDialog::apply()
{
  auto settings_model = getSourceModel(m_ui->m_setting_list_view->model());
  Q_ASSERT(settings_model);

  settings_model->apply();
}

void SettingsDialog::cancel()
{
  auto settings_model = getSourceModel(m_ui->m_setting_list_view->model());
  Q_ASSERT(settings_model);

  if (!settings_model->applied())
  {
    auto ret = QMessageBox::question(
      this, tr("Apply Settings"),
      tr("Are you sure that you want to discard changes settings?"),
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (ret == QMessageBox::Yes) close();
  } else
    close();
}

void SettingsDialog::currentChanged(QWidget *widget)
{
  m_ui->m_setting_search->setText(QLatin1String{});

  auto index = SettingsWidgetTreeModel::getIndexByWidget(
    *m_ui->m_setting_list_view->model(), widget, QModelIndex{});
  m_ui->m_setting_list_view->selectionModel()->select(
    index, QItemSelectionModel::ClearAndSelect);
}

void SettingsDialog::initUi()
{
  m_ui->setupUi(this);

  m_ui->m_setting_list_view->setModel(createStackedWidgetTreeModel());
  m_ui->m_setting_list_view->setItemDelegate(
    new utils::StackedWidgetTreeDelegate(this));
  m_ui->m_setting_list_view->expandAll();

  auto default_widget = new QLabel(
    tr("Select configuration element in the tree to edit its settings"), this);
  default_widget->setAlignment(Qt::AlignmentFlag::AlignCenter);

  m_ui->m_setting_widgets->setView(m_ui->m_setting_list_view);
  m_ui->m_setting_widgets->setDefaultWidget(default_widget);

  m_ui->m_setting_label->setView(m_ui->m_setting_list_view);

  m_ui->m_apply_button->setEnabled(false);
}

void SettingsDialog::initConnections()
{
  auto settings_model = qobject_cast<SettingsWidgetTreeModel *>(
    qobject_cast<QSortFilterProxyModel *>(m_ui->m_setting_list_view->model())
      ->sourceModel());

  connect(
    m_ui->m_setting_search, &QLineEdit::textChanged, this,
    &SettingsDialog::filterSettings);

  connect(
    settings_model, &SettingsWidgetTreeModel::appliedChanged, this,
    [this](auto applied) { m_ui->m_apply_button->setEnabled(!applied); });

  connect(
    m_ui->m_apply_button, &QPushButton::pressed, this, &SettingsDialog::apply);
  connect(
    m_ui->m_cancel_button, &QPushButton::pressed, this,
    &SettingsDialog::cancel);
  connect(m_ui->m_ok_button, &QPushButton::pressed, this, &SettingsDialog::ok);

  connect(
    m_ui->m_setting_label, &utils::QtStackedWidgetLabel::currentChanged, this,
    &SettingsDialog::currentChanged);

  QDesktopServices::setUrlHandler("settings", this, "setUrl");
}

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Settings"));
}

QAbstractItemModel *SettingsDialog::createStackedWidgetTreeModel()
{
  auto settings_root = {
    new utils::QtStackedWidgetTreeItem(
      QLatin1String("General"), new GeneralSettingsWidget(this),
      {new utils::QtStackedWidgetTreeItem(
        QLatin1String("Appearance"), new AppearanceSettingsWidget(this))}),
    new utils::QtStackedWidgetTreeItem(
      QLatin1String("Shortcuts"), new ShortcutsSettingsWidget(this)),
    new utils::QtStackedWidgetTreeItem(
      QLatin1String("Plugins"), new PluginSettingsWidget(this))};

  auto filter_model = new QSortFilterProxyModel(this);
  filter_model->setRecursiveFilteringEnabled(true);
  filter_model->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);

  filter_model->setSourceModel(
    new SettingsWidgetTreeModel(settings_root, filter_model));

  return filter_model;
}
