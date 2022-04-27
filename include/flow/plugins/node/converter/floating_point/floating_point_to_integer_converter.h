#ifndef PLUGIN_FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H
#define PLUGIN_FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class FLOATING_POINT_CONVERTER_API FloatingPointToIntegerConverter
    : public flow::node::TypeConverter
{
public:
  explicit FloatingPointToIntegerConverter() = default;
  ~FloatingPointToIntegerConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//PLUGIN_FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H
