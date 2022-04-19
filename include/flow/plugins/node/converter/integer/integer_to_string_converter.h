#ifndef FLOW_INTEGER_TO_STRING_CONVERTER_H
#define FLOW_INTEGER_TO_STRING_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class INTEGER_CONVERTER_API IntegerToStringConverter : public flow::node::TypeConverter
{
public:
  explicit IntegerToStringConverter() = default;
  ~IntegerToStringConverter() = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//FLOW_INTEGER_TO_STRING_CONVERTER_H
