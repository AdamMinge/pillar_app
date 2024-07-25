/* ----------------------------------- Local -------------------------------- */
#include "flow/condition_node/flow/dispatcher.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum class PinIn { True = 0, False = 1, Condition = 2 };
enum class PinOut { True = 0, False = 1 };

}  // namespace

/* ------------------------- ConditionNodeDispatcher ------------------------ */

namespace flow {

ConditionNodeDispatcher::ConditionNodeDispatcher() {
  setName(QObject::tr("IF"));

  auto true_value_pin = Pin({}, "True");
  auto false_value_pin = Pin({}, "False");
  auto condition_pin = Pin({}, "Condition");
  auto true_pin = Pin({}, "True");
  auto false_pin = Pin({}, "False");

  insertPin(Pin::Type::In, std::move(true_value_pin),
            static_cast<size_t>(PinIn::True));
  insertPin(Pin::Type::In, std::move(false_value_pin),
            static_cast<size_t>(PinIn::False));
  insertPin(Pin::Type::In, std::move(condition_pin),
            static_cast<size_t>(PinIn::Condition));
  insertPin(Pin::Type::Out, std::move(true_pin),
            static_cast<size_t>(PinOut::True));
  insertPin(Pin::Type::Out, std::move(false_pin),
            static_cast<size_t>(PinOut::False));
}

ConditionNodeDispatcher::~ConditionNodeDispatcher() = default;

std::unique_ptr<Node> ConditionNodeDispatcher::clone() const {
  auto node = std::make_unique<ConditionNodeDispatcher>();
  node->init(this);
  return std::move(node);
}

void ConditionNodeDispatcher::compute() {
  auto &true_value_pin =
      getPin(Pin::Type::In, static_cast<size_t>(PinIn::True));
  auto &false_value_pin =
      getPin(Pin::Type::In, static_cast<size_t>(PinIn::False));
  auto &condition_pin =
      getPin(Pin::Type::In, static_cast<size_t>(PinIn::Condition));
  auto &true_pin = getPin(Pin::Type::Out, static_cast<size_t>(PinOut::True));
  auto &false_pin = getPin(Pin::Type::Out, static_cast<size_t>(PinOut::False));

  const auto condition = condition_pin.getData().toBool();
  if (condition) {
    true_pin.setData(true_value_pin.getData());
  } else {
    false_pin.setData(false_value_pin.getData());
  }
}

}  // namespace flow
