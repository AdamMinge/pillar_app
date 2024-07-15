#ifndef LOGIC_NODE_VALUE_ITEM_H
#define LOGIC_NODE_VALUE_ITEM_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/node_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LogicNodeBoolEmittersChangeEvent;
class LogicNodeBoolEmitter;
class LogicNodeBoolReceiver;

/* ------------------------ LogicNodeBoolEmitterItem ------------------------ */

class LOGIC_NODE_API LogicNodeBoolEmitterItem : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit LogicNodeBoolEmitterItem(LogicNodeBoolEmitter *node,
                                    flow_document::FlowDocument *document,
                                    QGraphicsItem *parent);
  ~LogicNodeBoolEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent &event) override;
  void onUpdate(const LogicNodeBoolEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QCheckBox> m_widget;
  bool m_updating;
};

/* ----------------------- LogicNodeBoolReceiverItem ------------------------ */

class LOGIC_NODE_API LogicNodeBoolReceiverItem
    : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit LogicNodeBoolReceiverItem(LogicNodeBoolReceiver *node,
                                     flow_document::FlowDocument *document,
                                     QGraphicsItem *parent);
  ~LogicNodeBoolReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QCheckBox> m_widget;
};

#endif  // LOGIC_NODE_VALUE_ITEM_H
