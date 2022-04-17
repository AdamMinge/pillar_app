#ifndef FLOW_STRING_TO_BOOLEAN_CONVERTER_H
#define FLOW_STRING_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API StringToBooleanConverter : public node::TypeConverter
{
public:
  explicit StringToBooleanConverter() = default;
  ~StringToBooleanConverter() = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_STRING_TO_BOOLEAN_CONVERTER_H
