#ifndef MATH_NODE_VALUE_H
#define MATH_NODE_VALUE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- MathNodeFloatEmitter -------------------------- */

class MATH_NODE_API MathNodeFloatEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeFloatEmitter, flow_document::Node)

 public:
  explicit MathNodeFloatEmitter();
  ~MathNodeFloatEmitter() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

 protected:
  void compute() override;

 private:
  double m_value;
};

/* -------------------------- MathNodeFloatReceiver ------------------------- */

class MATH_NODE_API MathNodeFloatReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeFloatReceiver, flow_document::Node)

 public:
  explicit MathNodeFloatReceiver();
  ~MathNodeFloatReceiver() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(double value);
  [[nodiscard]] double getValue() const;

 protected:
  void compute() override;

 private:
  double m_value;
};

#endif  // MATH_NODE_VALUE_H
