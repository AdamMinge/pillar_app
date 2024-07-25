/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/insert.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Position = 1, Insert = 2 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ StringNodeInsert -------------------------- */

StringNodeInsert::StringNodeInsert() {
  setName(QObject::tr("INSERT"));

  getPin(Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(Pin::Type::In, PinIn::Position).setCaption("Position");
  getPin(Pin::Type::In, PinIn::Insert).setCaption("Insert");
}

StringNodeInsert::~StringNodeInsert() = default;

std::unique_ptr<Node> StringNodeInsert::clone() const {
  auto node = std::make_unique<StringNodeInsert>();
  node->init(this);
  return std::move(node);
}

void StringNodeInsert::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  const auto &position_pin = getPin(Pin::Type::In, PinIn::Position);
  const auto &insert_pin = getPin(Pin::Type::In, PinIn::Insert);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  auto value = value_pin.getData().toString();
  const auto position = position_pin.getData().toInt();
  const auto insert = insert_pin.getData().toString();

  result_pin.setData(value.insert(position, insert));
}

}  // namespace flow