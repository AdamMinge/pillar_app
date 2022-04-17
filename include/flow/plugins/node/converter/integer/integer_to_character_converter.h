#ifndef FLOW_INTEGER_TO_CHARACTER_CONVERTER_H
#define FLOW_INTEGER_TO_CHARACTER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API IntegerToCharacterConverter : public node::TypeConverter
{
public:
  explicit IntegerToCharacterConverter() = default;
  ~IntegerToCharacterConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_INTEGER_TO_CHARACTER_CONVERTER_H
