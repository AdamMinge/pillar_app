/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/count.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Search = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ StringNodeCount ------------------------- */

StringNodeCount::StringNodeCount() {
  setName(QObject::tr("COUNT"));

  getPin(Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(Pin::Type::In, PinIn::Search).setCaption("Search");
}

StringNodeCount::~StringNodeCount() = default;

std::unique_ptr<Node> StringNodeCount::clone() const {
  auto node = std::make_unique<StringNodeCount>();
  node->init(this);
  return std::move(node);
}

void StringNodeCount::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  const auto &search_pin = getPin(Pin::Type::In, PinIn::Search);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toString();
  const auto search = search_pin.getData().toString();

  result_pin.setData(value.count(search));
}

}  // namespace flow