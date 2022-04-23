/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/shortcuts_settings_widget.h"
#include "flow/editor/settings/shortcuts_table_delegate.h"
#include "flow/editor/settings/shortcuts_table_model.h"
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
  m_ui->m_shortcuts_table->setItemDelegateForColumn(
    ShortcutsTableModel::Column::ShortcutColumn,
    m_shortcuts_table_delegate.get());
  m_ui->m_shortcuts_table->horizontalHeader()->resizeSections(
    QHeaderView::ResizeToContents);
}

void ShortcutsSettingsWidget::initConnections()
{
  connect(
    m_ui->m_shortcuts_search, &QLineEdit::textChanged, this,
    &ShortcutsSettingsWidget::searchAction);

  connect(
    m_shortcuts_table_model.get(), &ShortcutsTableModel::appliedChanged, this,
    &ShortcutsSettingsWidget::appliedChanged);
}

void ShortcutsSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void ShortcutsSettingsWidget::searchAction(const QString &search)
{
  m_search_proxy_model->setFilterWildcard(search);
}

/* ---------------------- ShortcutsSettingsWidgetFactory -------------------- */

ShortcutsSettingsWidgetFactory::ShortcutsSettingsWidgetFactory(QObject *parent)
    : flow::settings::SettingsWidgetFactory(parent)
{

}

ShortcutsSettingsWidgetFactory::~ShortcutsSettingsWidgetFactory() = default;

std::unique_ptr<flow::settings::SettingsWidget>
ShortcutsSettingsWidgetFactory::create() const
{
  return std::make_unique<ShortcutsSettingsWidget>();
}
