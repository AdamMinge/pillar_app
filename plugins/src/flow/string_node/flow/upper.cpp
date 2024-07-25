/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/upper.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------- StringNodeUpper -------------------------- */

StringNodeUpper::StringNodeUpper() { setName(QObject::tr("UPPER")); }

StringNodeUpper::~StringNodeUpper() = default;

std::unique_ptr<Node> StringNodeUpper::clone() const {
  auto node = std::make_unique<StringNodeUpper>();
  node->init(this);
  return std::move(node);
}

void StringNodeUpper::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toString();

  result_pin.setData(value.toUpper());
}

}  // namespace flow