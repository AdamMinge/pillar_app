#ifndef MATH_NODE_VALUE_ITEM_H
#define MATH_NODE_VALUE_ITEM_H

/* ------------------------------------- Qt --------------------------------- */
#include <QDoubleSpinBox>
#include <QScopedPointer>
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/component/scene/item/node_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class MathNodeDoubleEmittersChangeEvent;
class MathNodeDoubleEmitter;
class MathNodeDoubleReceiver;

/* ------------------------ MathNodeDoubleEmitterItem ----------------------- */

class LIB_FLOW_MATH_NODE_API MathNodeDoubleEmitterItem : public NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeDoubleEmitterItem(MathNodeDoubleEmitter *node,
                                     FlowDocument *document,
                                     QGraphicsItem *parent);
  ~MathNodeDoubleEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent &event) override;
  void onUpdate(const MathNodeDoubleEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
  bool m_updating;
};

/* ------------------------ MathNodeDoubleReceiverItem -----------------------
 */

class LIB_FLOW_MATH_NODE_API MathNodeDoubleReceiverItem : public NodeItem {
  Q_OBJECT

 public:
  explicit MathNodeDoubleReceiverItem(MathNodeDoubleReceiver *node,
                                      FlowDocument *document,
                                      QGraphicsItem *parent);
  ~MathNodeDoubleReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QDoubleSpinBox> m_widget;
};

}  // namespace flow

#endif  // MATH_NODE_VALUE_ITEM_H
