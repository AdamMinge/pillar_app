#ifndef MATH_NODE_VALUE_H
#define MATH_NODE_VALUE_H

/* ------------------------------------- Qt --------------------------------- */
#include <QDoubleSpinBox>
#include <QScopedPointer>
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

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

/* -------------------------- MathNodeFloatReceiver ------------------------- */

class MATH_NODE_API MathNodeFloatReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeFloatReceiver, flow_document::Node)

 public:
  explicit MathNodeFloatReceiver();
  ~MathNodeFloatReceiver() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

#endif  // MATH_NODE_VALUE_H
