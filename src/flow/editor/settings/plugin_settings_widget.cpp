/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/plugin_settings_widget.h"

#include "flow/editor/settings/plugin_list_delegate.h"
#include "flow/editor/settings/plugin_list_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* --------------------------------- LibFlow -------------------------------- */
#include <flow/libflow/document/document.h>
#include <flow/libflow/document/document_manager.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_plugin_settings_widget.h"
/* -------------------------------------------------------------------------- */

/* --------------------------- PluginSettingsWidget ------------------------- */

PluginSettingsWidget::PluginSettingsWidget(QWidget *parent)
    : SettingsWidget(parent),
      m_ui(new Ui::PluginSettingsWidget()),
      m_plugin_list_model(new DynamicPluginListModel()),
      m_plugin_list_delegate(new PluginListDelegate()),
      m_search_proxy_model(new QSortFilterProxyModel()) {
  initUi();
  initConnections();

  retranslateUi();
}

PluginSettingsWidget::~PluginSettingsWidget() = default;

bool PluginSettingsWidget::apply() { return m_plugin_list_model->apply(); }

bool PluginSettingsWidget::applied() const {
  return m_plugin_list_model->applied();
}

void PluginSettingsWidget::changeEvent(QEvent *event) {
  QWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void PluginSettingsWidget::initUi() {
  m_ui->setupUi(this);

  m_search_proxy_model->setSourceModel(m_plugin_list_model.get());
  m_search_proxy_model->setFilterRole(PluginListModel::Role::PluginName);

  m_ui->m_plugin_list_view->setModel(m_search_proxy_model.get());
  m_ui->m_plugin_list_view->setItemDelegate(m_plugin_list_delegate.get());

  checkAvailability();
}

void PluginSettingsWidget::initConnections() {
  connect(m_ui->m_plugin_search, &QLineEdit::textChanged, this,
          &PluginSettingsWidget::searchPlugin);

  connect(m_plugin_list_model.get(), &PluginListModel::appliedChanged, this,
          &PluginSettingsWidget::appliedChanged);

  connect(&flow::DocumentManager::getInstance(),
          &flow::DocumentManager::currentDocumentChanged, this,
          &PluginSettingsWidget::checkAvailability);
}

void PluginSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void PluginSettingsWidget::searchPlugin(const QString &search) {
  m_search_proxy_model->setFilterWildcard(search);
}

void PluginSettingsWidget::checkAvailability() {
  m_ui->m_plugin_list_view->setEnabled(
      flow::DocumentManager::getInstance().getDocuments().empty());
}

/* ------------------------ PluginSettingsWidgetFactory --------------------- */

PluginSettingsWidgetFactory::PluginSettingsWidgetFactory(QObject *parent)
    : flow::SettingsWidgetFactory(parent) {}

PluginSettingsWidgetFactory::~PluginSettingsWidgetFactory() = default;

std::unique_ptr<flow::SettingsWidget> PluginSettingsWidgetFactory::create()
    const {
  return std::make_unique<PluginSettingsWidget>();
}
