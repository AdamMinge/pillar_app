#ifndef FLOW_NODE_DATA_H
#define FLOW_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class NODE_API NodeData : public QObject
  {
    Q_OBJECT

  public:
    explicit NodeData() = default;
    ~NodeData() override = default;

    virtual void assign(const NodeData &data) = 0;
  };

}// namespace node

Q_DECLARE_INTERFACE(node::NodeData, "org.flow.NodeData")

#endif//FLOW_NODE_DATA_H
