#ifndef FLOW_LOGIC_NODE_VALUE_H
#define FLOW_LOGIC_NODE_VALUE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

class LIB_FLOW_LOGIC_NODE_API LogicNodeBoolEmitter : public Node {
  FLOW_OBJECT_CLASS(LogicNodeBoolEmitter, Node)

 public:
  explicit LogicNodeBoolEmitter();
  ~LogicNodeBoolEmitter() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

 protected:
  void compute() override;

 private:
  bool m_value;
};

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

class LIB_FLOW_LOGIC_NODE_API LogicNodeBoolReceiver : public Node {
  FLOW_OBJECT_CLASS(LogicNodeBoolReceiver, Node)

 public:
  explicit LogicNodeBoolReceiver();
  ~LogicNodeBoolReceiver() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

 protected:
  void compute() override;

 private:
  bool m_value;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_VALUE_H
