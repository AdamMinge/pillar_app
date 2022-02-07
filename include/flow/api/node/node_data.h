#ifndef FLOW_INTERFACE_NODE_DATA_H
#define FLOW_INTERFACE_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
/* -------------------------------------------------------------------------- */

namespace api::node
{

  class API_API INodeData
  {
  public:
    explicit INodeData() = default;
    virtual ~INodeData() = default;

    [[nodiscard]] virtual QString getId() const = 0;
    [[nodiscard]] virtual QString getName() const = 0;
  };

}// namespace api::node

#endif//FLOW_INTERFACE_NODE_DATA_H
