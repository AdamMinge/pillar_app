#ifndef LOGIC_NODE_OR_H
#define LOGIC_NODE_OR_H

/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "logic_node.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeOr : public LogicNodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeOr, LogicNodeWithTwoParams)

 public:
  explicit LogicNodeOr();
  ~LogicNodeOr() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // LOGIC_NODE_OR_H
