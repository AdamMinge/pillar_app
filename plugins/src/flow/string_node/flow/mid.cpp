/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/mid.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Position = 1, Length = 2 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* -------------------------------- StringNodeMid --------------------------- */

StringNodeMid::StringNodeMid() {
  setName(QObject::tr("MID"));

  getPin(Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(Pin::Type::In, PinIn::Position).setCaption("Position");
  getPin(Pin::Type::In, PinIn::Length).setCaption("Length");
}

StringNodeMid::~StringNodeMid() = default;

std::unique_ptr<Node> StringNodeMid::clone() const {
  auto node = std::make_unique<StringNodeMid>();
  node->init(this);
  return std::move(node);
}

void StringNodeMid::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  const auto &position_pin = getPin(Pin::Type::In, PinIn::Position);
  const auto &length_pin = getPin(Pin::Type::In, PinIn::Length);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  auto value = value_pin.getData().toString();
  const auto position = position_pin.getData().toInt();
  const auto length = length_pin.getData().toInt();

  result_pin.setData(value.mid(position, length));
}

}  // namespace flow
