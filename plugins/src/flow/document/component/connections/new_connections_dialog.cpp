/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/connections/new_connections_dialog.h"

#include "flow/document/command/add_remove_connection.h"
#include "flow/document/document.h"
#include "flow/document/flow/node_layer.h"
/* -------------------------------- Standard -------------------------------- */
#include <limits>
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow/document/ui_new_connections_dialog.h"
/* -------------------------------------------------------------------------- */

namespace flow {

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

void NewConnectionsDialog::setNodeLayer(NodeLayer *layer) {
  for (auto i = 0; i < m_ui->m_layers->count(); ++i) {
    auto node_layer = m_ui->m_layers->itemData(i).value<NodeLayer *>();
    if (node_layer == layer) {
      m_ui->m_layers->setCurrentIndex(i);
      break;
    }
  }
}

void NewConnectionsDialog::accept() {
  auto node_layer = m_ui->m_layers->currentData().value<NodeLayer *>();

  auto entires = std::list<ConnectionEntry>{};
  entires.emplace_back(ConnectionEntry{node_layer,
                                       std::move(createConnection()),
                                       node_layer->connectionsCount()});
  m_document->getUndoStack()->push(
      new AddConnections(m_document, std::move(entires)));

  QDialog::accept();
}

std::unique_ptr<Connection> NewConnectionsDialog::createConnection() const {
  const auto output_node = m_ui->m_output_nodes->currentData().value<Node *>();
  const auto output_pin = m_ui->m_output_pins->currentData().value<size_t>();

  const auto input_node = m_ui->m_input_nodes->currentData().value<Node *>();
  const auto input_pin = m_ui->m_input_pins->currentData().value<size_t>();

  auto connection = std::make_unique<Connection>();
  connection->setOutputSide(ConnectionSide(output_node->getId(), output_pin));
  connection->setInputSide(ConnectionSide(input_node->getId(), input_pin));
  connection->setName(
      QString("%1[%2] -> %3[%4]")
          .arg(output_node->getName(),
               output_node->getPin(Pin::Type::Out, output_pin).getCaption(),
               input_node->getName(),
               input_node->getPin(Pin::Type::In, input_pin).getCaption()));

  return connection;
}

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
  connect(m_ui->m_layers, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::fillInputNodes);
  connect(m_ui->m_layers, &QComboBox::currentIndexChanged, this,
          &NewConnectionsDialog::fillOutputNodes);

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
  const auto layers = getAllLayers<NodeLayer>(m_document);

  m_ui->m_layers->clear();
  m_ui->m_layers->addItem(tr("- Select Layer -"));
  for (const auto layer : layers) {
    m_ui->m_layers->addItem(layer->getName(), QVariant::fromValue(layer));
  }

  m_ui->m_layers->setCurrentIndex(0);
}

void NewConnectionsDialog::fillInputNodes() {
  const auto node_layer =
      m_ui->m_layers->itemData(m_ui->m_layers->currentIndex())
          .value<NodeLayer *>();
  const auto nodes_count = node_layer ? node_layer->nodesCount() : 0;

  m_ui->m_input_nodes->clear();
  m_ui->m_input_nodes->addItem(tr("- Select Node -"));
  for (auto i = 0; i < nodes_count; ++i) {
    auto node = node_layer->nodeAt(i);
    if (node->getPinsCounts(Pin::Type::In) <= 0) continue;

    m_ui->m_input_nodes->addItem(node->getName(), QVariant::fromValue(node));
  }

  m_ui->m_input_nodes->setCurrentIndex(0);
}

void NewConnectionsDialog::fillOutputNodes() {
  const auto node_layer =
      m_ui->m_layers->itemData(m_ui->m_layers->currentIndex())
          .value<NodeLayer *>();
  const auto nodes_count = node_layer ? node_layer->nodesCount() : 0;

  m_ui->m_output_nodes->clear();
  m_ui->m_output_nodes->addItem(tr("- Select Node -"));
  for (auto i = 0; i < nodes_count; ++i) {
    auto node = node_layer->nodeAt(i);
    if (node->getPinsCounts(Pin::Type::Out) <= 0) continue;

    m_ui->m_output_nodes->addItem(node->getName(), QVariant::fromValue(node));
  }

  m_ui->m_output_nodes->setCurrentIndex(0);
}

void NewConnectionsDialog::fillInputPins() {
  const auto node = m_ui->m_input_nodes->currentData().value<Node *>();
  const auto pins_counts = node ? node->getPinsCounts(Pin::Type::In) : 0;

  m_ui->m_input_pins->clear();
  m_ui->m_input_pins->addItem(
      tr("- Select Pin -"),
      QVariant::fromValue(std::numeric_limits<size_t>::max()));

  for (size_t pin_index = 0; pin_index < pins_counts; ++pin_index) {
    const auto &pin = node->getPin(Pin::Type::In, pin_index);
    m_ui->m_input_pins->addItem(pin.getCaption(),
                                QVariant::fromValue(pin_index));
  }
}

void NewConnectionsDialog::fillOutputPins() {
  const auto node = m_ui->m_output_nodes->currentData().value<Node *>();
  const auto pins_counts = node ? node->getPinsCounts(Pin::Type::Out) : 0;

  m_ui->m_output_pins->clear();
  m_ui->m_output_pins->addItem(
      tr("- Select Pin -"),
      QVariant::fromValue(std::numeric_limits<size_t>::max()));

  for (size_t pin_index = 0; pin_index < pins_counts; ++pin_index) {
    const auto &pin = node->getPin(Pin::Type::Out, pin_index);
    m_ui->m_output_pins->addItem(pin.getCaption(),
                                 QVariant::fromValue(pin_index));
  }
}

void NewConnectionsDialog::validate() {
  const auto node_layer =
      m_ui->m_layers->itemData(m_ui->m_layers->currentIndex())
          .value<NodeLayer *>();

  const auto output_node = m_ui->m_output_nodes->currentData().value<Node *>();
  const auto input_node = m_ui->m_input_nodes->currentData().value<Node *>();

  const auto output_pin = m_ui->m_output_pins->currentData().value<size_t>();
  const auto input_pin = m_ui->m_input_pins->currentData().value<size_t>();

  const auto can_connect =
      node_layer
          ? node_layer->canConnect(
                ConnectionSide(output_node ? output_node->getId() : QUuid{},
                               output_pin),
                ConnectionSide(input_node ? input_node->getId() : QUuid{},
                               input_pin))
          : false;

  m_ui->m_connect_button->setEnabled(can_connect);
}

}  // namespace flow