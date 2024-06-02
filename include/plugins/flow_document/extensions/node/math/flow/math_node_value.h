#ifndef MATH_NODE_VALUE_H
#define MATH_NODE_VALUE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- MathNodeDoubleEmitter ------------------------- */

class MATH_NODE_API MathNodeDoubleEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeDoubleEmitter, flow_document::Node)

 public:
  explicit MathNodeDoubleEmitter();
  ~MathNodeDoubleEmitter() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

 protected:
  void compute() override;

 private:
  double m_value;
};

/* -------------------------- MathNodeDoubleReceiver ------------------------ */

class MATH_NODE_API MathNodeDoubleReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeDoubleReceiver, flow_document::Node)

 public:
  explicit MathNodeDoubleReceiver();
  ~MathNodeDoubleReceiver() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

 protected:
  void compute() override;

 private:
  double m_value;
};

#endif  // MATH_NODE_VALUE_H
