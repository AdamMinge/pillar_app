/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_settings_widget.h"
#include "flow/editor/settings/shortcuts_table_delegate.h"
#include "flow/editor/settings/shortcuts_table_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMenu>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/action_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_shortcuts_settings_widget.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- ShortcutsSettingsWidget ----------------------- */

ShortcutsSettingsWidget::ShortcutsSettingsWidget(QWidget *parent)
    : SettingsWidget(parent), m_ui(new Ui::ShortcutsSettingsWidget()),
      m_shortcuts_table_model(new ShortcutsTableModel()),
      m_shortcuts_table_delegate(new ShortcutsTableDelegate()),
      m_search_proxy_model(new QSortFilterProxyModel())
{
  initUi();
  initConnections();

  retranslateUi();
}

ShortcutsSettingsWidget::~ShortcutsSettingsWidget() = default;

bool ShortcutsSettingsWidget::apply()
{
  return m_shortcuts_table_model->apply();
}

bool ShortcutsSettingsWidget::applied() const
{
  return m_shortcuts_table_model->applied();
}

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

void ShortcutsSettingsWidget::initUi()
{
  m_ui->setupUi(this);

  m_search_proxy_model->setSourceModel(m_shortcuts_table_model.get());
  m_search_proxy_model->setFilterRole(Qt::DisplayRole);
  m_search_proxy_model->setFilterKeyColumn(
    ShortcutsTableModel::Column::ActionColumn);
  m_search_proxy_model->sort(ShortcutsTableModel::Column::ActionColumn);

  m_ui->m_shortcuts_table->setModel(m_search_proxy_model.get());
  m_ui->m_shortcuts_table->hideColumn(
    ShortcutsTableModel::Column::ActionIdColumn);
  m_ui->m_shortcuts_table->hideColumn(ShortcutsTableModel::Column::ValidColumn);
  m_ui->m_shortcuts_table->hideColumn(
    ShortcutsTableModel::Column::AppliedColumn);
  m_ui->m_shortcuts_table->setItemDelegate(m_shortcuts_table_delegate.get());
  m_ui->m_shortcuts_table->horizontalHeader()->resizeSections(
    QHeaderView::ResizeToContents);
}

void ShortcutsSettingsWidget::initConnections()
{
  connect(
    m_ui->m_shortcuts_search, &QLineEdit::textChanged, this,
    &ShortcutsSettingsWidget::searchAction);

  connect(
    m_shortcuts_table_model.get(), &ShortcutsTableModel::dataChanged,
    [this]() { Q_EMIT appliedChanged(applied()); });

  connect(
    m_ui->m_shortcuts_table, &QTableView::customContextMenuRequested, this,
    &ShortcutsSettingsWidget::contextMenu);
}

void ShortcutsSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void ShortcutsSettingsWidget::searchAction(const QString &search)
{
  m_search_proxy_model->setFilterWildcard(search);
}

void ShortcutsSettingsWidget::contextMenu(const QPoint &pos)
{
  const auto selected_rows =
    m_ui->m_shortcuts_table->selectionModel()->selectedRows();

  if(!selected_rows.empty())
  {
    auto menu = new QMenu;
    menu->addAction(tr("Set to Default"), [&selected_rows, this]() {
      setDefaultShortcuts(selected_rows);
    });
    menu->addAction(
      tr("Clear"), [selected_rows, this]() { clearShortcuts(selected_rows); });

    menu->exec(m_ui->m_shortcuts_table->viewport()->mapToGlobal(pos));
  }
}

void ShortcutsSettingsWidget::setDefaultShortcuts(
  const QList<QModelIndex> &indexes)
{
  for (const auto &index : indexes)
  {
    const auto action_id_index = m_search_proxy_model->index(
      index.row(), ShortcutsTableModel::Column::ActionIdColumn);
    const auto action_shortcut_index = m_search_proxy_model->index(
      index.row(), ShortcutsTableModel::Column::ShortcutColumn);

    const auto action_id =
      m_search_proxy_model->data(action_id_index, Qt::DisplayRole).toString();
    const auto action_default_shortcut =
      flow::ActionManager::getInstance().getDefaultShortcut(action_id);

    m_search_proxy_model->setData(
      action_shortcut_index, action_default_shortcut, Qt::DisplayRole);
  }
}

void ShortcutsSettingsWidget::clearShortcuts(const QList<QModelIndex> &indexes)
{
  for (const auto &index : indexes)
  {
    const auto action_shortcut_index = m_search_proxy_model->index(
      index.row(), ShortcutsTableModel::Column::ShortcutColumn);

    m_search_proxy_model->setData(
      action_shortcut_index, QVariant{}, Qt::DisplayRole);
  }
}

/* ---------------------- ShortcutsSettingsWidgetFactory -------------------- */

ShortcutsSettingsWidgetFactory::ShortcutsSettingsWidgetFactory(QObject *parent)
    : flow::settings::SettingsWidgetFactory(parent)
{}

ShortcutsSettingsWidgetFactory::~ShortcutsSettingsWidgetFactory() = default;

std::unique_ptr<flow::settings::SettingsWidget>
ShortcutsSettingsWidgetFactory::create() const
{
  return std::make_unique<ShortcutsSettingsWidget>();
}
