/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/replace.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Before = 1, After = 2 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ StringNodeReplace ------------------------- */

StringNodeReplace::StringNodeReplace() {
  setName(QObject::tr("REPLACE"));

  getPin(Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(Pin::Type::In, PinIn::Before).setCaption("Before");
  getPin(Pin::Type::In, PinIn::After).setCaption("After");
}

StringNodeReplace::~StringNodeReplace() = default;

std::unique_ptr<Node> StringNodeReplace::clone() const {
  auto node = std::make_unique<StringNodeReplace>();
  node->init(this);
  return std::move(node);
}

void StringNodeReplace::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  const auto &before_pin = getPin(Pin::Type::In, PinIn::Before);
  const auto &after_pin = getPin(Pin::Type::In, PinIn::After);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  auto value = value_pin.getData().toString();
  const auto before = before_pin.getData().toString();
  const auto after = after_pin.getData().toString();

  result_pin.setData(value.replace(before, after));
}

}  // namespace flow
