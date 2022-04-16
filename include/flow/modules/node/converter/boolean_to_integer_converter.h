#ifndef FLOW_BOOLEAN_TO_INTEGER_CONVERTER_H
#define FLOW_BOOLEAN_TO_INTEGER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API BooleanToIntegerConverter : public TypeConverter
  {
  public:
    explicit BooleanToIntegerConverter() = default;
    ~BooleanToIntegerConverter() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_BOOLEAN_TO_INTEGER_CONVERTER_H
