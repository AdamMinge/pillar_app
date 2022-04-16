#ifndef FLOW_TYPE_CONVERTER_H
#define FLOW_TYPE_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::data
{
  class NodeData;
}

namespace node::converter
{

  class NODE_API TypeConverter
  {
  public:
    explicit TypeConverter() = default;
    ~TypeConverter() = default;

    [[nodiscard]] virtual std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) = 0;
  };

}// namespace node::converter

#endif//FLOW_TYPE_CONVERTER_H
