/* ----------------------------------- Local -------------------------------- */
#include "condition_node_if.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0, Condition = 1 };
enum PinOut { True = 0, False = 1 };

}  // namespace

/* ----------------------------- ConditionNodeIf ---------------------------- */

ConditionNodeIf::ConditionNodeIf() {
  setName(QObject::tr("IF"));

  auto value_pin = flow_document::Pin({}, "Value");
  auto condition_pin = flow_document::Pin({}, "Condition");
  auto true_pin = flow_document::Pin({}, "True");
  auto false_pin = flow_document::Pin({}, "False");

  insertPin(flow_document::Pin::Type::In, std::move(value_pin), Value);
  insertPin(flow_document::Pin::Type::In, std::move(condition_pin), Condition);
  insertPin(flow_document::Pin::Type::Out, std::move(true_pin), True);
  insertPin(flow_document::Pin::Type::Out, std::move(false_pin), False);
}

ConditionNodeIf::~ConditionNodeIf() = default;

std::unique_ptr<flow_document::Node> ConditionNodeIf::clone() const {
  auto node = std::make_unique<ConditionNodeIf>();
  node->init(this);
  return std::move(node);
}

void ConditionNodeIf::compute() {
  auto &value_pin = getPin(flow_document::Pin::Type::In, Value);
  auto &condition_pin = getPin(flow_document::Pin::Type::In, Condition);
  auto &true_pin = getPin(flow_document::Pin::Type::Out, True);
  auto &false_pin = getPin(flow_document::Pin::Type::Out, False);

  const auto value = value_pin.getData();
  const auto condition = condition_pin.getData().toBool();

  if (condition) {
    true_pin.setData(value);
  } else {
    false_pin.setData(value);
  }
}
