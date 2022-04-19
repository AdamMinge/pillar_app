#ifndef FLOW_NODE_PAINTER_H
#define FLOW_NODE_PAINTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class Node;

  class LIB_FLOW_API NodePainter
  {
  public:
    static void paint(QPainter *painter, const Node *node);

  public:
    explicit NodePainter() = delete;
  };

}// namespace flow::node

#endif//FLOW_NODE_PAINTER_H
