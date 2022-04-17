#ifndef FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H
#define FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API IntegerToFloatingPointConverter : public node::TypeConverter
{
public:
  explicit IntegerToFloatingPointConverter() = default;
  ~IntegerToFloatingPointConverter() = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H
