/* ----------------------------------- Local -------------------------------- */
#include "logic_node_value.h"
/* -------------------------------------------------------------------------- */

LogicNodeValue::LogicNodeValue()
    : m_widget(new QCheckBox(QObject::tr("Value"))) {
  setName(QObject::tr("BOOL"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);
}

LogicNodeValue::~LogicNodeValue() = default;

QWidget *LogicNodeValue::getEmbeddedWidget() const { return m_widget.get(); }

std::unique_ptr<flow_document::Node> LogicNodeValue::clone() const {
  auto node = std::make_unique<LogicNodeValue>();
  node->init(this);
  return std::move(node);
}

void LogicNodeValue::compute() {}
