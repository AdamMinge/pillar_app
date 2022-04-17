#ifndef FLOW_STRING_TO_INTEGER_CONVERTER_H
#define FLOW_STRING_TO_INTEGER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API StringToIntegerConverter : public node::TypeConverter
{
public:
  explicit StringToIntegerConverter() = default;
  ~StringToIntegerConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_STRING_TO_INTEGER_CONVERTER_H
