#ifndef FLOW_CHARACTER_TO_INTEGER_CONVERTER_H
#define FLOW_CHARACTER_TO_INTEGER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API CharacterToIntegerConverter : public TypeConverter
  {
  public:
    explicit CharacterToIntegerConverter() = default;
    ~CharacterToIntegerConverter() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_CHARACTER_TO_INTEGER_CONVERTER_H
