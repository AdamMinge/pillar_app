/* ----------------------------------- Local -------------------------------- */
#include "string_node_contains.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0, Search = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ StringNodeContains ------------------------ */

StringNodeContains::StringNodeContains() {
  setName(QObject::tr("CONTAINS"));

  getPin(flow_document::Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(flow_document::Pin::Type::In, PinIn::Search).setCaption("Search");
}

StringNodeContains::~StringNodeContains() = default;

std::unique_ptr<flow_document::Node> StringNodeContains::clone() const {
  auto node = std::make_unique<StringNodeContains>();
  node->init(this);
  return std::move(node);
}

void StringNodeContains::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  const auto &search_pin = getPin(flow_document::Pin::Type::In, PinIn::Search);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toString();
  const auto search = search_pin.getData().toString();

  result_pin.setData(value.contains(search));
}
