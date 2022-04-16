#ifndef FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
#define FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API StringToFloatingPoint : public TypeConverter
  {
  public:
    explicit StringToFloatingPoint() = default;
    ~StringToFloatingPoint() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
