/* ----------------------------------- Local -------------------------------- */
#include "string_node_mid.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0, Position = 1, Length = 2 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------------- StringNodeMid --------------------------- */

StringNodeMid::StringNodeMid() {
  setName(QObject::tr("MID"));

  getPin(flow_document::Pin::Type::In, Value).setCaption("Value");
  getPin(flow_document::Pin::Type::In, Position).setCaption("Position");
  getPin(flow_document::Pin::Type::In, Length).setCaption("Length");
}

StringNodeMid::~StringNodeMid() = default;

std::unique_ptr<flow_document::Node> StringNodeMid::clone() const {
  auto node = std::make_unique<StringNodeMid>();
  node->init(this);
  return std::move(node);
}

void StringNodeMid::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, Value);
  const auto &position_pin = getPin(flow_document::Pin::Type::In, Position);
  const auto &length_pin = getPin(flow_document::Pin::Type::In, Length);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, Result);

  auto value = value_pin.getData().toString();
  const auto position = position_pin.getData().toInt();
  const auto length = length_pin.getData().toInt();

  result_pin.setData(value.mid(position, length));
}
