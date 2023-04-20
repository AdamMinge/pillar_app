/* ----------------------------------- Local -------------------------------- */
#include "logic_node_not.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/node/base/boolean_node_data.h>
/* -------------------------------------------------------------------------- */

LogicNodeNot::LogicNodeNot() { setName(QObject::tr("NOT")); }

LogicNodeNot::~LogicNodeNot() = default;

void LogicNodeNot::compute() {
  auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  auto value_A =
      dynamic_cast<const flow_document::BooleanNodeData &>(in_pin_0.getData())
          .getValue();

  const auto out_data = flow_document::BooleanNodeData(!value_A);
  out_pin.setData(out_data);
}
