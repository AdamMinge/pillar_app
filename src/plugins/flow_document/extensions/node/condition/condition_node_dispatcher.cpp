/* ----------------------------------- Local -------------------------------- */
#include "condition_node_dispatcher.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum class PinIn { True = 0, False = 1, Condition = 2 };
enum class PinOut { True = 0, False = 1 };

}  // namespace

/* ------------------------- ConditionNodeDispatcher ------------------------ */

ConditionNodeDispatcher::ConditionNodeDispatcher() {
  setName(QObject::tr("IF"));

  auto true_value_pin = flow_document::Pin({}, "True");
  auto false_value_pin = flow_document::Pin({}, "False");
  auto condition_pin = flow_document::Pin({}, "Condition");
  auto true_pin = flow_document::Pin({}, "True");
  auto false_pin = flow_document::Pin({}, "False");

  insertPin(flow_document::Pin::Type::In, std::move(true_value_pin),
            static_cast<size_t>(PinIn::True));
  insertPin(flow_document::Pin::Type::In, std::move(false_value_pin),
            static_cast<size_t>(PinIn::False));
  insertPin(flow_document::Pin::Type::In, std::move(condition_pin),
            static_cast<size_t>(PinIn::Condition));
  insertPin(flow_document::Pin::Type::Out, std::move(true_pin),
            static_cast<size_t>(PinOut::True));
  insertPin(flow_document::Pin::Type::Out, std::move(false_pin),
            static_cast<size_t>(PinOut::False));
}

ConditionNodeDispatcher::~ConditionNodeDispatcher() = default;

std::unique_ptr<flow_document::Node> ConditionNodeDispatcher::clone() const {
  auto node = std::make_unique<ConditionNodeDispatcher>();
  node->init(this);
  return std::move(node);
}

void ConditionNodeDispatcher::compute() {
  auto &true_value_pin =
      getPin(flow_document::Pin::Type::In, static_cast<size_t>(PinIn::True));
  auto &false_value_pin =
      getPin(flow_document::Pin::Type::In, static_cast<size_t>(PinIn::False));
  auto &condition_pin = getPin(flow_document::Pin::Type::In,
                               static_cast<size_t>(PinIn::Condition));
  auto &true_pin =
      getPin(flow_document::Pin::Type::Out, static_cast<size_t>(PinOut::True));
  auto &false_pin =
      getPin(flow_document::Pin::Type::Out, static_cast<size_t>(PinOut::False));

  const auto condition = condition_pin.getData().toBool();
  if (condition) {
    true_pin.setData(true_value_pin.getData());
  } else {
    false_pin.setData(false_value_pin.getData());
  }
}
