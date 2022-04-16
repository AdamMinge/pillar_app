#ifndef FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H
#define FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API FloatingPointToIntegerConverter : public TypeConverter
  {
  public:
    explicit FloatingPointToIntegerConverter() = default;
    ~FloatingPointToIntegerConverter() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H
