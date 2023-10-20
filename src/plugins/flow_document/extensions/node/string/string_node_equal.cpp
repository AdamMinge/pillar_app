/* ----------------------------------- Local -------------------------------- */
#include "string_node_equal.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- StringNodeEqual -------------------------- */

StringNodeEqual::StringNodeEqual() { setName(QObject::tr("EQUAL")); }

StringNodeEqual::~StringNodeEqual() = default;

std::unique_ptr<flow_document::Node> StringNodeEqual::clone() const {
  auto node = std::make_unique<StringNodeEqual>();
  node->init(this);
  return std::move(node);
}

void StringNodeEqual::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toString();
  const auto rhs = rhs_pin.getData().toString();

  result_pin.setData(lhs == rhs);
}
