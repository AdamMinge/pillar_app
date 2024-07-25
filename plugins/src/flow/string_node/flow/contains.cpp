/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/contains.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Search = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ StringNodeContains ------------------------ */

StringNodeContains::StringNodeContains() {
  setName(QObject::tr("CONTAINS"));

  getPin(Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(Pin::Type::In, PinIn::Search).setCaption("Search");
}

StringNodeContains::~StringNodeContains() = default;

std::unique_ptr<Node> StringNodeContains::clone() const {
  auto node = std::make_unique<StringNodeContains>();
  node->init(this);
  return std::move(node);
}

void StringNodeContains::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  const auto &search_pin = getPin(Pin::Type::In, PinIn::Search);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toString();
  const auto search = search_pin.getData().toString();

  result_pin.setData(value.contains(search));
}

}  // namespace flow