/* ----------------------------------- Local -------------------------------- */
#include "logic_node_or.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/node/base/boolean_node_data.h>
/* -------------------------------------------------------------------------- */

LogicNodeOr::LogicNodeOr() { setName(QObject::tr("OR")); }

LogicNodeOr::~LogicNodeOr() = default;

void LogicNodeOr::compute() {
  auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  auto &in_pin_1 = getPin(flow_document::Pin::Type::In, 1);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  auto value_A =
      dynamic_cast<const flow_document::BooleanNodeData &>(in_pin_0.getData())
          .getValue();
  auto value_B =
      dynamic_cast<const flow_document::BooleanNodeData &>(in_pin_1.getData())
          .getValue();

  const auto out_data = flow_document::BooleanNodeData(value_A | value_B);
  out_pin.setData(out_data);
}
