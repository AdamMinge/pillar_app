#ifndef FLOW_NODE_DATA_H
#define FLOW_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class NODE_API NodeData
  {
  public:
    explicit NodeData() = default;
    virtual ~NodeData() = default;

    virtual void assign(const NodeData &data) = 0;

    [[nodiscard]] virtual QString getId() const = 0;
    [[nodiscard]] virtual QString getName() const = 0;
  };

}// namespace node

#endif//FLOW_NODE_DATA_H
