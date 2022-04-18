#ifndef FLOW_NODE_PAINTER_H
#define FLOW_NODE_PAINTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class Node;

  class NODE_API NodePainter
  {
  public:
    static void paint(QPainter *painter, const Node* node);

  public:
    explicit NodePainter() = delete;
  };

}// namespace node

#endif//FLOW_NODE_PAINTER_H
