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

/* -------------------------- MathNodeValueEmitter -------------------------- */

class MATH_NODE_API MathNodeValueEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeValueEmitter, flow_document::Node)

 public:
  explicit MathNodeValueEmitter();
  ~MathNodeValueEmitter() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

/* -------------------------- MathNodeValueReceiver ------------------------- */

class MATH_NODE_API MathNodeValueReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(MathNodeValueReceiver, flow_document::Node)

 public:
  explicit MathNodeValueReceiver();
  ~MathNodeValueReceiver() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

#endif  // MATH_NODE_VALUE_H
