#ifndef PLUGIN_FLOW_INTEGER_TO_BOOLEAN_CONVERTER_H
#define PLUGIN_FLOW_INTEGER_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class INTEGER_CONVERTER_API IntegerToBooleanConverter : public flow::node::TypeConverter
{
public:
  explicit IntegerToBooleanConverter() = default;
  ~IntegerToBooleanConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_INTEGER_TO_BOOLEAN_CONVERTER_H
