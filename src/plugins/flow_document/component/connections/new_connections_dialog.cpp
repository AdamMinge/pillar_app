/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/connections/new_connections_dialog.h"

#include "flow_document/flow/connection_layer.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_new_connections_dialog.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

NewConnectionsDialog::NewConnectionsDialog(FlowDocument *document,
                                           QWidget *parent)
    : QDialog(parent),
      m_ui(new Ui::NewConnectionsDialog()),
      m_document(document) {
  initUi();
  initConnections();
  retranslateUi();

  validate();
}

NewConnectionsDialog::~NewConnectionsDialog() = default;

void NewConnectionsDialog::accept() { QDialog::accept(); }

void NewConnectionsDialog::changeEvent(QEvent *event) {
  QDialog::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NewConnectionsDialog::initUi() {
  m_ui->setupUi(this);

  fillLayers();
  fillInputNodes();
  fillOutputNodes();
}

void NewConnectionsDialog::initConnections() {
  connect(m_ui->m_input_nodes, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::fillInputPins);
  connect(m_ui->m_output_nodes, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::fillOutputPins);

  connect(m_ui->m_layers, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::validate);
  connect(m_ui->m_input_pins, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::validate);
  connect(m_ui->m_output_pins, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::validate);
}

void NewConnectionsDialog::retranslateUi() { m_ui->retranslateUi(this); }

void NewConnectionsDialog::fillLayers() {
  auto layers = getAllLayers<ConnectionLayer>(m_document);

  m_ui->m_layers->clear();
  for (auto layer : layers) {
    m_ui->m_layers->addItem(layer->getName(), QVariant::fromValue(layer));
  }

  m_ui->m_layers->setCurrentIndex(-1);
}

void NewConnectionsDialog::fillInputNodes() {
  auto nodes = getAllNodes(m_document);

  m_ui->m_input_nodes->clear();
  for (auto node : nodes) {
    const auto has_input_pins = node->getPinsCounts(Pin::Type::In) > 0;

    if (has_input_pins) {
      m_ui->m_input_nodes->addItem(node->getName(), QVariant::fromValue(node));
    }
  }

  m_ui->m_input_nodes->setCurrentIndex(-1);
}

void NewConnectionsDialog::fillOutputNodes() {
  auto nodes = getAllNodes(m_document);

  m_ui->m_output_nodes->clear();
  for (auto node : nodes) {
    const auto has_output_pins = node->getPinsCounts(Pin::Type::Out) > 0;

    if (has_output_pins) {
      m_ui->m_output_nodes->addItem(node->getName(), QVariant::fromValue(node));
    }
  }

  m_ui->m_output_nodes->setCurrentIndex(-1);
}

void NewConnectionsDialog::fillInputPins() {
  const auto current_index = m_ui->m_input_nodes->currentIndex();
  const auto node =
      m_ui->m_input_nodes->itemData(current_index).value<Node *>();
  const auto pins_counts = node->getPinsCounts(Pin::Type::In);

  m_ui->m_input_pins->clear();
  for (auto pin_index = 0; pin_index < pins_counts; ++pin_index) {
    const auto &pin = node->getPin(Pin::Type::In, pin_index);
    m_ui->m_input_pins->addItem(pin.getCaption(), pin_index);
  }
}

void NewConnectionsDialog::fillOutputPins() {
  const auto current_index = m_ui->m_output_nodes->currentIndex();
  const auto node =
      m_ui->m_output_nodes->itemData(current_index).value<Node *>();
  const auto pins_counts = node->getPinsCounts(Pin::Type::Out);

  m_ui->m_output_pins->clear();
  for (auto pin_index = 0; pin_index < pins_counts; ++pin_index) {
    const auto &pin = node->getPin(Pin::Type::Out, pin_index);
    m_ui->m_output_pins->addItem(pin.getCaption(), pin_index);
  }
}

void NewConnectionsDialog::validate() {
  auto connection_layer =
      m_ui->m_layers->itemData(m_ui->m_layers->currentIndex())
          .value<ConnectionLayer *>();

  auto outut_node =
      m_ui->m_output_nodes->itemData(m_ui->m_output_nodes->currentIndex())
          .value<Node *>();
  auto input_node =
      m_ui->m_input_nodes->itemData(m_ui->m_input_nodes->currentIndex())
          .value<Node *>();

  m_ui->m_connect_button->setEnabled(connection_layer && outut_node &&
                                     input_node);
}

}  // namespace flow_document