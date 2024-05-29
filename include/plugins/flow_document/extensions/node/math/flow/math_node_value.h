#ifndef MATH_NODE_VALUE_H
#define MATH_NODE_VALUE_H

/* ------------------------------------- Qt --------------------------------- */
#include <QDoubleSpinBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/node_item.h>
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MathNodeFloatEmittersChangeEvent;

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

/* ------------------------ MathNodeFloatEmitterItem ------------------------ */

class MATH_NODE_API MathNodeFloatEmitterItem : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeFloatEmitterItem(flow_document::Node *node,
                                    flow_document::FlowDocument *document,
                                    QGraphicsItem *parent);
  ~MathNodeFloatEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent &event) override;
  void onUpdate(const MathNodeFloatEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
  bool m_updating;
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

/* ------------------------ MathNodeFloatReceiverItem ----------------------- */

class MATH_NODE_API MathNodeFloatReceiverItem : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeFloatReceiverItem(flow_document::Node *node,
                                     flow_document::FlowDocument *document,
                                     QGraphicsItem *parent);
  ~MathNodeFloatReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

#endif  // MATH_NODE_VALUE_H
