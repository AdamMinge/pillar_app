#ifndef FLOW_NODE_DATA_H
#define FLOW_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::data
{

  class NODE_API NodeData : public QObject
  {
    Q_OBJECT

  public:
    explicit NodeData() = default;
    ~NodeData() override = default;

    virtual void assign(const NodeData &data) = 0;
  };

}// namespace node::data

#endif//FLOW_NODE_DATA_H
