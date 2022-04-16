#ifndef FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H
#define FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API IntegerToFloatingPointConverter : public TypeConverter
  {
  public:
    explicit IntegerToFloatingPointConverter() = default;
    ~IntegerToFloatingPointConverter() = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_INTEGER_TO_FLOATING_POINT_COVERTER_H
