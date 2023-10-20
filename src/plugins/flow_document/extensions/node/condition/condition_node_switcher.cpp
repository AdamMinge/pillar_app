/* ----------------------------------- Local -------------------------------- */
#include "condition_node_switcher.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { True = 0, False = 1, Condition = 2 };
enum PinOut { Result = 0 };

}  // namespace

/* --------------------------- ConditionNodeSwitcher------------------------- */

ConditionNodeSwitcher::ConditionNodeSwitcher() {
  setName(QObject::tr("IF"));

  getPin(flow_document::Pin::Type::In, PinIn::True).setCaption("True");
  getPin(flow_document::Pin::Type::In, PinIn::False).setCaption("False");
  getPin(flow_document::Pin::Type::In, PinIn::Condition)
      .setCaption("Condition");
}

ConditionNodeSwitcher::~ConditionNodeSwitcher() = default;

std::unique_ptr<flow_document::Node> ConditionNodeSwitcher::clone() const {
  auto node = std::make_unique<ConditionNodeSwitcher>();
  node->init(this);
  return std::move(node);
}

void ConditionNodeSwitcher::compute() {
  auto &true_value_pin = getPin(flow_document::Pin::Type::In, PinIn::True);
  auto &false_value_pin = getPin(flow_document::Pin::Type::In, PinIn::False);
  auto &condition_pin = getPin(flow_document::Pin::Type::In, PinIn::Condition);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto condition = condition_pin.getData().toBool();

  result_pin.setData(condition ? true_value_pin.getData()
                               : false_value_pin.getData());
}
