#ifndef FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H
#define FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API FloatingPointToBooleanConverter : public node::TypeConverter
{
public:
  explicit FloatingPointToBooleanConverter() = default;
  ~FloatingPointToBooleanConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H
