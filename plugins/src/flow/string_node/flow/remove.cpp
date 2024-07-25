/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/remove.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0, Remove = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ StringNodeRemove -------------------------- */

StringNodeRemove::StringNodeRemove() {
  setName(QObject::tr("REMOVE"));

  getPin(Pin::Type::In, PinIn::Value).setCaption("Value");
  getPin(Pin::Type::In, PinIn::Remove).setCaption("Remove");
}

StringNodeRemove::~StringNodeRemove() = default;

std::unique_ptr<Node> StringNodeRemove::clone() const {
  auto node = std::make_unique<StringNodeRemove>();
  node->init(this);
  return std::move(node);
}

void StringNodeRemove::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  const auto &remove_pin = getPin(Pin::Type::In, PinIn::Remove);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  auto value = value_pin.getData().toString();
  const auto remove = remove_pin.getData().toString();

  result_pin.setData(value.remove(remove));
}

}  // namespace flow