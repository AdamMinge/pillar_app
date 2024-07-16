/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node_lower.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- StringNodeLower -------------------------- */

StringNodeLower::StringNodeLower() { setName(QObject::tr("LOWER")); }

StringNodeLower::~StringNodeLower() = default;

std::unique_ptr<flow_document::Node> StringNodeLower::clone() const {
  auto node = std::make_unique<StringNodeLower>();
  node->init(this);
  return std::move(node);
}

void StringNodeLower::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toString();

  result_pin.setData(value.toLower());
}
