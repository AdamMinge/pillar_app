/* ----------------------------------- Local -------------------------------- */
#include "logic_node_value.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- LogicNodeValueEmitter ------------------------- */

LogicNodeValueEmitter::LogicNodeValueEmitter()
    : m_widget(new QCheckBox(QObject::tr("Bool"))) {
  setName(QObject::tr("BOOL_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);

  m_widget->connect(m_widget.get(), &QCheckBox::toggled,
                    [this]() { compute(); });
}

LogicNodeValueEmitter::~LogicNodeValueEmitter() = default;

QWidget *LogicNodeValueEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> LogicNodeValueEmitter::clone() const {
  auto node = std::make_unique<LogicNodeValueEmitter>();
  node->init(this);
  return std::move(node);
}

void LogicNodeValueEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);
  const auto value = m_widget->checkState() & Qt::CheckState::Checked;

  out_pin.setData(value);
}

/* -------------------------- LogicNodeValueReceiver ------------------------ */

LogicNodeValueReceiver::LogicNodeValueReceiver()
    : m_widget(new QCheckBox(QObject::tr("Bool"))) {
  setName(QObject::tr("BOOL_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);

  m_widget->setCheckable(false);
}

LogicNodeValueReceiver::~LogicNodeValueReceiver() = default;

QWidget *LogicNodeValueReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> LogicNodeValueReceiver::clone() const {
  auto node = std::make_unique<LogicNodeValueReceiver>();
  node->init(this);
  return std::move(node);
}

void LogicNodeValueReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  const auto value = in_pin.getData().toBool();

  m_widget->setCheckState(value ? Qt::CheckState::Checked
                                : Qt::CheckState::Unchecked);
}
