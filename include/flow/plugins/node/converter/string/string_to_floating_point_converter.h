#ifndef FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
#define FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API StringToFloatingPoint : public node::TypeConverter
{
public:
  explicit StringToFloatingPoint() = default;
  ~StringToFloatingPoint() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_STRING_TO_FLOATING_POINT_CONVERTER_H
