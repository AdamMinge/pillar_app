#ifndef FLOW_BOOLEAN_TO_FLOATING_POINT_CONVERTER_H
#define FLOW_BOOLEAN_TO_FLOATING_POINT_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API BooleanToFloatingPointConverter : public node::TypeConverter
{
public:
  explicit BooleanToFloatingPointConverter() = default;
  ~BooleanToFloatingPointConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_BOOLEAN_TO_FLOATING_POINT_CONVERTER_H
