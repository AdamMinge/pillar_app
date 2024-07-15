/* ----------------------------------- Local -------------------------------- */
#include "settings/settings_dialog.h"

#include "settings/settings_widget_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QCloseEvent>
#include <QDesktopServices>
#include <QLabel>
#include <QMessageBox>
#include <QSortFilterProxyModel>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/stacked_widget/stacked_widget_tree_delegate.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

SettingsDialog::SettingsDialog(QWidget *parent)
    : qtils::QtDialogWithUrlLinks<SettingsDialog>(parent),
      m_ui(new Ui::SettingsDialog()),
      m_settings_widget_model(new SettingsWidgetTreeModel),
      m_settings_widget_filter_model(new QSortFilterProxyModel) {
  QDesktopServices::setUrlHandler("settings", this, "setUrl");

  initUi();
  initConnections();
  retranslateUi();
}

SettingsDialog::~SettingsDialog() {
  QDesktopServices::unsetUrlHandler("settings");
}

void SettingsDialog::setUrl(const QUrl &url) {
  if (url.scheme() != QLatin1String("settings")) return;

  auto model = m_ui->m_setting_list_view->model();
  auto index = SettingsWidgetTreeModel::getIndexBy(
      *model, SettingsWidgetTreeModel::Role::ObjectNameRole,
      url.toString(QUrl::RemoveScheme), QModelIndex{});

  if (!index.isValid()) m_ui->m_setting_search->setText(QLatin1String{});

  m_ui->m_setting_list_view->selectionModel()->select(
      index, QItemSelectionModel::ClearAndSelect);
}

void SettingsDialog::closeEvent(QCloseEvent *event) {
  if (!m_settings_widget_model->applied()) {
    auto ret = QMessageBox::question(
        this, tr("Apply Settings"),
        tr("Are you sure that you want to discard changes settings?"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (ret == QMessageBox::No) {
      event->ignore();
      return;
    }
  }

  event->accept();
}

void SettingsDialog::changeEvent(QEvent *event) {
  QDialog::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void SettingsDialog::filterSettings(const QString &filter) {
  m_settings_widget_filter_model->setFilterWildcard(filter);
}

void SettingsDialog::ok() {
  apply();
  cancel();
}

void SettingsDialog::apply() { m_settings_widget_model->apply(); }

void SettingsDialog::cancel() { close(); }

void SettingsDialog::currentChanged(QWidget *widget) {
  m_ui->m_setting_search->setText(QLatin1String{});

  auto index = SettingsWidgetTreeModel::getIndexBy(
      *m_ui->m_setting_list_view->model(),
      SettingsWidgetTreeModel::Role::WidgetRole, QVariant::fromValue(widget),
      QModelIndex{});

  m_ui->m_setting_list_view->selectionModel()->select(
      index, QItemSelectionModel::ClearAndSelect);
}

void SettingsDialog::initUi() {
  m_ui->setupUi(this);

  m_settings_widget_filter_model->setRecursiveFilteringEnabled(true);
  m_settings_widget_filter_model->setFilterCaseSensitivity(
      Qt::CaseSensitivity::CaseInsensitive);
  m_settings_widget_filter_model->setSourceModel(m_settings_widget_model.get());

  m_ui->m_setting_list_view->setModel(m_settings_widget_filter_model.get());
  m_ui->m_setting_list_view->setItemDelegate(
      new qtils::StackedWidgetTreeDelegate(this));
  m_ui->m_setting_list_view->expandAll();

  auto default_widget = new QLabel(
      tr("Select configuration element in the tree to edit its settings"),
      this);
  default_widget->setAlignment(Qt::AlignmentFlag::AlignCenter);

  m_ui->m_setting_widgets->setView(m_ui->m_setting_list_view);
  m_ui->m_setting_widgets->setDefaultWidget(default_widget);

  m_ui->m_setting_label->setView(m_ui->m_setting_list_view);

  m_ui->m_apply_button->setEnabled(false);
}

void SettingsDialog::initConnections() {
  auto settings_model = qobject_cast<SettingsWidgetTreeModel *>(
      qobject_cast<QSortFilterProxyModel *>(m_ui->m_setting_list_view->model())
          ->sourceModel());

  connect(m_ui->m_setting_search, &QLineEdit::textChanged, this,
          &SettingsDialog::filterSettings);

  connect(settings_model, &SettingsWidgetTreeModel::appliedChanged, this,
          [this](auto applied) { m_ui->m_apply_button->setEnabled(!applied); });

  connect(m_ui->m_apply_button, &QPushButton::pressed, this,
          &SettingsDialog::apply);
  connect(m_ui->m_cancel_button, &QPushButton::pressed, this,
          &SettingsDialog::cancel);
  connect(m_ui->m_ok_button, &QPushButton::pressed, this, &SettingsDialog::ok);

  connect(m_ui->m_setting_label, &qtils::QtStackedWidgetLabel::currentChanged,
          this, &SettingsDialog::currentChanged);
}

void SettingsDialog::retranslateUi() {
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Settings"));
}
