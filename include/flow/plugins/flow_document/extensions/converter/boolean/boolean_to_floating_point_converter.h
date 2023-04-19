#ifndef PLUGIN_FLOW_BOOLEAN_TO_FLOATING_POINT_CONVERTER_H
#define PLUGIN_FLOW_BOOLEAN_TO_FLOATING_POINT_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class BOOLEAN_CONVERTER_API BooleanToFloatingPointConverter
    : public flow::node::TypeConverter
{
public:
  explicit BooleanToFloatingPointConverter() = default;
  ~BooleanToFloatingPointConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_BOOLEAN_TO_FLOATING_POINT_CONVERTER_H
