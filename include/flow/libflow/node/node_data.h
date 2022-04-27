#ifndef FLOW_NODE_DATA_H
#define FLOW_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class LIB_FLOW_API NodeData
  {
  public:
    explicit NodeData() = default;
    virtual ~NodeData() = default;

    virtual void assign(const NodeData &data) = 0;
  };

}// namespace flow::node

#endif//FLOW_NODE_DATA_H
