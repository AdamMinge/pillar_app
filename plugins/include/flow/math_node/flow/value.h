#ifndef MATH_NODE_VALUE_H
#define MATH_NODE_VALUE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- MathNodeDoubleEmitter ------------------------- */

class LIB_FLOW_MATH_NODE_API MathNodeDoubleEmitter : public Node {
  FLOW_OBJECT_CLASS(MathNodeDoubleEmitter, Node)

 public:
  explicit MathNodeDoubleEmitter();
  ~MathNodeDoubleEmitter() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

 protected:
  void compute() override;

 private:
  double m_value;
};

/* -------------------------- MathNodeDoubleReceiver ------------------------ */

class LIB_FLOW_MATH_NODE_API MathNodeDoubleReceiver : public Node {
  FLOW_OBJECT_CLASS(MathNodeDoubleReceiver, Node)

 public:
  explicit MathNodeDoubleReceiver();
  ~MathNodeDoubleReceiver() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

 protected:
  void compute() override;

 private:
  double m_value;
};

}  // namespace flow

#endif  // MATH_NODE_VALUE_H
