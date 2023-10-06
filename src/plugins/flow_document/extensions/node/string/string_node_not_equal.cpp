/* ----------------------------------- Local -------------------------------- */
#include "string_node_not_equal.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ StringNodeNotEqual ------------------------ */

StringNodeNotEqual::StringNodeNotEqual() { setName(QObject::tr("NOT EQUAL")); }

StringNodeNotEqual::~StringNodeNotEqual() = default;

std::unique_ptr<flow_document::Node> StringNodeNotEqual::clone() const {
  auto node = std::make_unique<StringNodeNotEqual>();
  node->init(this);
  return std::move(node);
}

void StringNodeNotEqual::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, Result);

  const auto lhs = lhs_pin.getData().toString();
  const auto rhs = rhs_pin.getData().toString();

  result_pin.setData(lhs != rhs);
}
