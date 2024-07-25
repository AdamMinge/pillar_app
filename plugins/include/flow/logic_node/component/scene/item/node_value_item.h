#ifndef FLOW_LOGIC_NODE_NODE_VALUE_ITEM_H
#define FLOW_LOGIC_NODE_NODE_VALUE_ITEM_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/scene/item/node_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LogicNodeBoolEmittersChangeEvent;
class LogicNodeBoolEmitter;
class LogicNodeBoolReceiver;

/* ------------------------ LogicNodeBoolEmitterItem ------------------------ */

class LIB_FLOW_LOGIC_NODE_API LogicNodeBoolEmitterItem : public NodeItem {
  Q_OBJECT

 public:
  explicit LogicNodeBoolEmitterItem(LogicNodeBoolEmitter *node,
                                    FlowDocument *document,
                                    QGraphicsItem *parent);
  ~LogicNodeBoolEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent &event) override;
  void onUpdate(const LogicNodeBoolEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QCheckBox> m_widget;
  bool m_updating;
};

/* ----------------------- LogicNodeBoolReceiverItem ------------------------ */

class LIB_FLOW_LOGIC_NODE_API LogicNodeBoolReceiverItem : public NodeItem {
  Q_OBJECT

 public:
  explicit LogicNodeBoolReceiverItem(LogicNodeBoolReceiver *node,
                                     FlowDocument *document,
                                     QGraphicsItem *parent);
  ~LogicNodeBoolReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QCheckBox> m_widget;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_NODE_VALUE_ITEM_H
