#ifndef MATH_NODE_VALUE_ITEM_H
#define MATH_NODE_VALUE_ITEM_H

/* ------------------------------------- Qt --------------------------------- */
#include <QDoubleSpinBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/node_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MathNodeFloatEmittersChangeEvent;
class MathNodeFloatEmitter;
class MathNodeFloatReceiver;

/* ------------------------ MathNodeFloatEmitterItem ------------------------ */

class MATH_NODE_API MathNodeFloatEmitterItem : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeFloatEmitterItem(MathNodeFloatEmitter *node,
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

/* ------------------------ MathNodeFloatReceiverItem ----------------------- */

class MATH_NODE_API MathNodeFloatReceiverItem : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeFloatReceiverItem(MathNodeFloatReceiver *node,
                                     flow_document::FlowDocument *document,
                                     QGraphicsItem *parent);
  ~MathNodeFloatReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

#endif  // MATH_NODE_VALUE_ITEM_H
