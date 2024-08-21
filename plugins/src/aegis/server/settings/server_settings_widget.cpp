/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/settings/server_settings_widget.h"

/* ----------------------------------- Aegis -------------------------------- */
#include <aegis/manager.h>
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

  onChangeServer();
  onChangeSniffer();
}

void ServerSettingsWidget::initConnections() {
  connect(m_ui->m_server_checkbox, &QCheckBox::stateChanged, this,
          &ServerSettingsWidget::switchServerState);

  connect(m_ui->m_sniffer_checkbox, &QCheckBox::stateChanged, this,
          &ServerSettingsWidget::switchSnifferState);

  connect(m_ui->m_color_picker, &qtils::QtColorPicker::valueChanged, this,
          &ServerSettingsWidget::switchMarkerColor);
}

void ServerSettingsWidget::retranslateUi() { m_ui->retranslateUi(this); }

void ServerSettingsWidget::onChangeServer() {
  const auto isRunning = server()->isListening();

  const auto blocker = QSignalBlocker(m_ui->m_server_checkbox);

  m_ui->m_server_checkbox->setCheckState(isRunning ? Qt::CheckState::Checked
                                                   : Qt::CheckState::Unchecked);
  if (isRunning) {
    const auto port =
        server()->serverPort() ? QString::number(server()->serverPort()) : "";
    m_ui->m_port_edit->setText(port);
  }

  m_ui->m_port_edit->setDisabled(isRunning);
}

void ServerSettingsWidget::onChangeSniffer() {
  const auto running = sniffer()->isSniffing();
  const auto marker_color = sniffer()->getMarkerColor();

  const auto blocker = QSignalBlocker(m_ui->m_sniffer_checkbox);

  m_ui->m_sniffer_checkbox->setCheckState(running ? Qt::CheckState::Checked
                                                  : Qt::CheckState::Unchecked);
  m_ui->m_color_picker->setValue(marker_color);
}

void ServerSettingsWidget::switchServerState(int state) {
  switch (state) {
    case Qt::CheckState::Checked: {
      const auto port = m_ui->m_port_edit->text().toUInt();
      server()->listen(QHostAddress::Any, port);
      break;
    }

    case Qt::CheckState::Unchecked: {
      server()->close();
      break;
    }
  }

  onChangeServer();
}

void ServerSettingsWidget::switchSnifferState(int state) {
  switch (state) {
    case Qt::CheckState::Checked:
      sniffer()->start();
      break;

    case Qt::CheckState::Unchecked:
      sniffer()->stop();
      break;
  }

  onChangeSniffer();
}

void ServerSettingsWidget::switchMarkerColor(QColor color) {
  sniffer()->setMarkerColor(color);

  onChangeSniffer();
}

/* ------------------------ ServerSettingsWidgetFactory --------------------- */

ServerSettingsWidgetFactory::ServerSettingsWidgetFactory(QObject *parent)
    : pillar::SettingsWidgetFactory(parent) {}

ServerSettingsWidgetFactory::~ServerSettingsWidgetFactory() = default;

std::unique_ptr<pillar::SettingsWidget> ServerSettingsWidgetFactory::create()
    const {
  return std::make_unique<ServerSettingsWidget>();
}

QString ServerSettingsWidgetFactory::getParentObjectName() const {
  return QLatin1String("PluginSettingsWidget");
}

}  // namespace aegis
