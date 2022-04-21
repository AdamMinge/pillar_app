#ifndef PLUGIN_FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H
#define PLUGIN_FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class FLOATING_POINT_CONVERTER_API FloatingPointToBooleanConverter : public flow::node::TypeConverter
{
public:
  explicit FloatingPointToBooleanConverter() = default;
  ~FloatingPointToBooleanConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_FLOATING_POINT_TO_BOOLEAN_CONVERTER_H
