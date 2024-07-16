/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node_insert.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Position = 1, Insert = 2 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ StringNodeInsert -------------------------- */

StringNodeInsert::StringNodeInsert() {
  setName(QObject::tr("INSERT"));

  getPin(flow_document::Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(flow_document::Pin::Type::In, PinIn::Position).setCaption("Position");
  getPin(flow_document::Pin::Type::In, PinIn::Insert).setCaption("Insert");
}

StringNodeInsert::~StringNodeInsert() = default;

std::unique_ptr<flow_document::Node> StringNodeInsert::clone() const {
  auto node = std::make_unique<StringNodeInsert>();
  node->init(this);
  return std::move(node);
}

void StringNodeInsert::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  const auto &position_pin =
      getPin(flow_document::Pin::Type::In, PinIn::Position);
  const auto &insert_pin = getPin(flow_document::Pin::Type::In, PinIn::Insert);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  auto value = value_pin.getData().toString();
  const auto position = position_pin.getData().toInt();
  const auto insert = insert_pin.getData().toString();

  result_pin.setData(value.insert(position, insert));
}
