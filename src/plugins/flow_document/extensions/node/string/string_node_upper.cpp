/* ----------------------------------- Local -------------------------------- */
#include "string_node_upper.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- StringNodeUpper -------------------------- */

StringNodeUpper::StringNodeUpper() { setName(QObject::tr("UPPER")); }

StringNodeUpper::~StringNodeUpper() = default;

std::unique_ptr<flow_document::Node> StringNodeUpper::clone() const {
  auto node = std::make_unique<StringNodeUpper>();
  node->init(this);
  return std::move(node);
}

void StringNodeUpper::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toString();

  result_pin.setData(value.toUpper());
}
