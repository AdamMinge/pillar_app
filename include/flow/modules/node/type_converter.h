#ifndef FLOW_TYPE_CONVERTER_H
#define FLOW_TYPE_CONVERTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class NodeData;

  class NODE_API TypeConverter
  {
  public:
    explicit TypeConverter() = default;
    virtual ~TypeConverter() = default;

    [[nodiscard]] virtual std::unique_ptr<NodeData>
    convert(const NodeData &data) = 0;
  };

}// namespace node

#endif//FLOW_TYPE_CONVERTER_H
