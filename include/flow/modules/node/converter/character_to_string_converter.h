#ifndef FLOW_CHARACTER_TO_STRING_CONVERTER_H
#define FLOW_CHARACTER_TO_STRING_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/type_converter.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API CharacterToStringConverter : public TypeConverter
  {
  public:
    explicit CharacterToStringConverter() = default;
    ~CharacterToStringConverter() override = default;

    [[nodiscard]] std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) override;
  };

}// namespace node::converter

#endif//FLOW_CHARACTER_TO_STRING_CONVERTER_H
