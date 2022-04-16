#ifndef FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H
#define FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API FloatingPointToBooleanConverter : public TypeConverter
  {
  public:
    explicit FloatingPointToBooleanConverter() = default;
    ~FloatingPointToBooleanConverter() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H
