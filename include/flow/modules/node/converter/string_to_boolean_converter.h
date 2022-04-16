#ifndef FLOW_STRING_TO_BOOLEAN_CONVERTER_H
#define FLOW_STRING_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API StringToBooleanConverter : public TypeConverter
  {
  public:
    explicit StringToBooleanConverter() = default;
    ~StringToBooleanConverter() = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_STRING_TO_BOOLEAN_CONVERTER_H
