/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/plugin_settings_widget.h"
#include "flow/editor/settings/plugin_list_delegate.h"
#include "flow/editor/settings/plugin_list_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_plugin_settings_widget.h"
/* -------------------------------------------------------------------------- */

/* --------------------------- PluginSettingsWidget ------------------------- */

PluginSettingsWidget::PluginSettingsWidget(QWidget *parent)
    : SettingsWidget(parent), m_ui(new Ui::PluginSettingsWidget()),
      m_plugin_list_model(new DynamicPluginListModel()),
      m_plugin_list_delegate(new PluginListDelegate()),
      m_search_proxy_model(new QSortFilterProxyModel())
{
  initUi();
  initConnections();

  retranslateUi();
}

PluginSettingsWidget::~PluginSettingsWidget() = default;

bool PluginSettingsWidget::apply() { return m_plugin_list_model->apply(); }

bool PluginSettingsWidget::applied() const
{
  return m_plugin_list_model->applied();
}

void PluginSettingsWidget::changeEvent(QEvent *event)
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

void PluginSettingsWidget::initUi()
{
  m_ui->setupUi(this);

  m_plugin_list_delegate->setIconSize(QSize(64, 64));
  m_plugin_list_delegate->setMargins(QMargins(10, 5, 10, 5));
  m_plugin_list_delegate->setSpacing(10, 15);

  m_search_proxy_model->setSourceModel(m_plugin_list_model.get());
  m_search_proxy_model->setFilterRole(PluginListModel::Role::PluginName);

  m_ui->m_plugin_list_view->setModel(m_search_proxy_model.get());
  m_ui->m_plugin_list_view->setItemDelegate(m_plugin_list_delegate.get());
}

void PluginSettingsWidget::initConnections()
{
  connect(
    m_ui->m_plugin_search, &QLineEdit::textChanged, this,
    &PluginSettingsWidget::searchPlugin);

  connect(
    m_plugin_list_model.get(), &PluginListModel::appliedChanged, this,
    &PluginSettingsWidget::appliedChanged);
}

void PluginSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void PluginSettingsWidget::searchPlugin(const QString &search)
{
  m_search_proxy_model->setFilterWildcard(search);
}

/* ------------------------ PluginSettingsWidgetFactory --------------------- */

PluginSettingsWidgetFactory::PluginSettingsWidgetFactory(QObject *parent)
    : flow::settings::SettingsWidgetFactory(parent)
{}

PluginSettingsWidgetFactory::~PluginSettingsWidgetFactory() = default;

std::unique_ptr<flow::settings::SettingsWidget>
PluginSettingsWidgetFactory::create() const
{
  return std::make_unique<PluginSettingsWidget>();
}
