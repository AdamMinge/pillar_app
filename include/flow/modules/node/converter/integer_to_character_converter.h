#ifndef FLOW_INTEGER_TO_CHARACTER_CONVERTER_H
#define FLOW_INTEGER_TO_CHARACTER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API IntegerToCharacterConverter : public TypeConverter
  {
  public:
    explicit IntegerToCharacterConverter() = default;
    ~IntegerToCharacterConverter() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_INTEGER_TO_CHARACTER_CONVERTER_H
