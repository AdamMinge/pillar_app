#ifndef FLOW_INTERFACE_TYPE_CONVERTER_H
#define FLOW_INTERFACE_TYPE_CONVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
/* -------------------------------------------------------------------------- */

namespace api::node
{

  class INodeData;

  class API_API ITypeConverter
  {
  public:
    explicit ITypeConverter() = default;
    virtual ~ITypeConverter() = default;

    virtual std::shared_ptr<INodeData>
    convert(std::shared_ptr<INodeData> data) = 0;
  };

}// namespace api::node

#endif//FLOW_INTERFACE_TYPE_CONVERTER_H
