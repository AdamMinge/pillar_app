#ifndef LOGIC_NODE_AND_H
#define LOGIC_NODE_AND_H

/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "logic_node.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeAnd : public LogicNodeWithTwoParams {
 public:
  explicit LogicNodeAnd();
  ~LogicNodeAnd() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // LOGIC_NODE_AND_H
