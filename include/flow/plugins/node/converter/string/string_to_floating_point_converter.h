#ifndef FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
#define FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter.h>
/* -------------------------------------------------------------------------- */

class STRING_CONVERTER_API StringToFloatingPoint : public flow::node::TypeConverter
{
public:
  explicit StringToFloatingPoint() = default;
  ~StringToFloatingPoint() override = default;

  [[nodiscard]] std::unique_ptr<flow::node::NodeData>
  convert(const flow::node::NodeData &data) override;
};

#endif//FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
