#ifndef PLUGIN_FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
#define PLUGIN_FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/export.h"
/* -------------------------------------------------------------------------- */

class STRING_CONVERTER_API StringToFloatingPoint
    : public flow::node::TypeConverter
{
public:
  explicit StringToFloatingPoint() = default;
  ~StringToFloatingPoint() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
