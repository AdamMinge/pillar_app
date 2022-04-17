#ifndef FLOW_CHARACTER_TO_STRING_CONVERTER_H
#define FLOW_CHARACTER_TO_STRING_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API CharacterToStringConverter : public node::TypeConverter
{
public:
  explicit CharacterToStringConverter() = default;
  ~CharacterToStringConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_CHARACTER_TO_STRING_CONVERTER_H
