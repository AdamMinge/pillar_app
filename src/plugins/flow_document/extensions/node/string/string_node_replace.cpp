/* ----------------------------------- Local -------------------------------- */
#include "string_node_replace.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0, Before = 1, After = 2 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ StringNodeReplace ------------------------- */

StringNodeReplace::StringNodeReplace() {
  setName(QObject::tr("REPLACE"));

  getPin(flow_document::Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(flow_document::Pin::Type::In, PinIn::Before).setCaption("Before");
  getPin(flow_document::Pin::Type::In, PinIn::After).setCaption("After");
}

StringNodeReplace::~StringNodeReplace() = default;

std::unique_ptr<flow_document::Node> StringNodeReplace::clone() const {
  auto node = std::make_unique<StringNodeReplace>();
  node->init(this);
  return std::move(node);
}

void StringNodeReplace::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  const auto &before_pin = getPin(flow_document::Pin::Type::In, PinIn::Before);
  const auto &after_pin = getPin(flow_document::Pin::Type::In, PinIn::After);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  auto value = value_pin.getData().toString();
  const auto before = before_pin.getData().toString();
  const auto after = after_pin.getData().toString();

  result_pin.setData(value.replace(before, after));
}
