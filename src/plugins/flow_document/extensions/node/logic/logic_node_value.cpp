/* ----------------------------------- Local -------------------------------- */
#include "logic_node_value.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

LogicNodeBoolEmitter::LogicNodeBoolEmitter()
    : m_widget(new QCheckBox(QObject::tr("Bool"))) {
  setName(QObject::tr("BOOL_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);

  m_widget->connect(m_widget.get(), &QCheckBox::toggled,
                    [this]() { compute(); });
}

LogicNodeBoolEmitter::~LogicNodeBoolEmitter() = default;

QWidget *LogicNodeBoolEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> LogicNodeBoolEmitter::clone() const {
  auto node = std::make_unique<LogicNodeBoolEmitter>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);
  const auto value = m_widget->checkState() & Qt::CheckState::Checked;

  out_pin.setData(value);
}

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

LogicNodeBoolReceiver::LogicNodeBoolReceiver()
    : m_widget(new QCheckBox(QObject::tr("Bool"))) {
  setName(QObject::tr("BOOL_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);

  m_widget->setDisabled(true);
}

LogicNodeBoolReceiver::~LogicNodeBoolReceiver() = default;

QWidget *LogicNodeBoolReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> LogicNodeBoolReceiver::clone() const {
  auto node = std::make_unique<LogicNodeBoolReceiver>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  const auto value = in_pin.getData().toBool();

  m_widget->setCheckState(value ? Qt::CheckState::Checked
                                : Qt::CheckState::Unchecked);
}
