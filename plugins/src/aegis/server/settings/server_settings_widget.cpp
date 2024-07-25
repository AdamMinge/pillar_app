/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/settings/server_settings_widget.h"

#include "aegis/server/server_manager.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QRegularExpressionValidator>
/* ------------------------------------ Ui ---------------------------------- */
#include "settings/ui_server_settings_widget.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* --------------------------- ServerSettingsWidget ------------------------- */

ServerSettingsWidget::ServerSettingsWidget(QWidget *parent)
    : SettingsWidget(parent), m_ui(new Ui::ServerSettingsWidget()) {
  initUi();
  initConnections();

  retranslateUi();
}

ServerSettingsWidget::~ServerSettingsWidget() = default;

bool ServerSettingsWidget::apply() { return true; }

bool ServerSettingsWidget::applied() const { return true; }

void ServerSettingsWidget::changeEvent(QEvent *event) {
  QWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ServerSettingsWidget::initUi() {
  m_ui->setupUi(this);

  auto validator = new QRegularExpressionValidator(
      QRegularExpression("(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]"
                         "{3}|[1-5][0-9]{4}|[1-9][0-9]{0,3}|0)"),
      this);
  m_ui->m_port_edit->setValidator(validator);
}

void ServerSettingsWidget::initConnections() {
  connect(m_ui->m_server_checkbox, &QCheckBox::stateChanged, this,
          &ServerSettingsWidget::switchServerState);
}

void ServerSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void ServerSettingsWidget::switchServerState(int state) {
  auto &server_manager = ServerManager::getInstance();

  switch (state) {
    case Qt::CheckState::Checked: {
      const auto port = m_ui->m_port_edit->text().toUInt();
      server_manager.start(QHostAddress::Any, port);
      break;
    }

    case Qt::CheckState::Unchecked:
      server_manager.stop();
      break;
  }
}

/* ------------------------ ServerSettingsWidgetFactory --------------------- */

ServerSettingsWidgetFactory::ServerSettingsWidgetFactory(QObject *parent)
    : pillar::SettingsWidgetFactory(parent) {}

ServerSettingsWidgetFactory::~ServerSettingsWidgetFactory() = default;

std::unique_ptr<pillar::SettingsWidget> ServerSettingsWidgetFactory::create()
    const {
  return std::make_unique<ServerSettingsWidget>();
}

}  // namespace aegis
