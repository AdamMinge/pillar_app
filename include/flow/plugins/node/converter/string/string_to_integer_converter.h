#ifndef PLUGIN_FLOW_STRING_TO_INTEGER_CONVERTER_H
#define PLUGIN_FLOW_STRING_TO_INTEGER_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class STRING_CONVERTER_API StringToIntegerConverter : public flow::node::TypeConverter
{
public:
  explicit StringToIntegerConverter() = default;
  ~StringToIntegerConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_STRING_TO_INTEGER_CONVERTER_H
