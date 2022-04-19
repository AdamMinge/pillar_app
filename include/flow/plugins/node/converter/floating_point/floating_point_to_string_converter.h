#ifndef FLOW_FLOATING_POINT_TO_STRING_CONVERTER_H
#define FLOW_FLOATING_POINT_TO_STRING_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class FLOATING_POINT_CONVERTER_API FloatingPointToStringConverter : public flow::node::TypeConverter
{
public:
  explicit FloatingPointToStringConverter() = default;
  ~FloatingPointToStringConverter() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//FLOW_FLOATING_POINT_TO_STRING_CONVERTER_H
