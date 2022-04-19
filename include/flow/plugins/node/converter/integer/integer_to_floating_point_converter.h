#ifndef FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H
#define FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class INTEGER_CONVERTER_API IntegerToFloatingPointConverter : public flow::node::TypeConverter
{
public:
  explicit IntegerToFloatingPointConverter() = default;
  ~IntegerToFloatingPointConverter() = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H
