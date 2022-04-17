#ifndef FLOW_BOOLEAN_TO_INTEGER_CONVERTER_H
#define FLOW_BOOLEAN_TO_INTEGER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API BooleanToIntegerConverter : public node::TypeConverter
{
public:
  explicit BooleanToIntegerConverter() = default;
  ~BooleanToIntegerConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_BOOLEAN_TO_INTEGER_CONVERTER_H
