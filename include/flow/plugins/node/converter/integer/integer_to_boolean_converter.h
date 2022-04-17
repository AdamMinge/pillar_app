#ifndef FLOW_INTEGER_TO_BOOLEAN_CONVERTER_H
#define FLOW_INTEGER_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API IntegerToBooleanConverter : public node::TypeConverter
{
public:
  explicit IntegerToBooleanConverter() = default;
  ~IntegerToBooleanConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_INTEGER_TO_BOOLEAN_CONVERTER_H
