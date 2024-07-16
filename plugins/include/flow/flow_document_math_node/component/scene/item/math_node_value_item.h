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

class MathNodeDoubleEmittersChangeEvent;
class MathNodeDoubleEmitter;
class MathNodeDoubleReceiver;

/* ------------------------ MathNodeDoubleEmitterItem ----------------------- */

class MATH_NODE_API MathNodeDoubleEmitterItem : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeDoubleEmitterItem(MathNodeDoubleEmitter *node,
                                     flow_document::FlowDocument *document,
                                     QGraphicsItem *parent);
  ~MathNodeDoubleEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent &event) override;
  void onUpdate(const MathNodeDoubleEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
  bool m_updating;
};

/* ------------------------ MathNodeDoubleReceiverItem -----------------------
 */

class MATH_NODE_API MathNodeDoubleReceiverItem
    : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeDoubleReceiverItem(MathNodeDoubleReceiver *node,
                                      flow_document::FlowDocument *document,
                                      QGraphicsItem *parent);
  ~MathNodeDoubleReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

#endif  // MATH_NODE_VALUE_ITEM_H
