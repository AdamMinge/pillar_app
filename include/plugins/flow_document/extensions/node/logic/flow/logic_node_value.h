#ifndef LOGIC_NODE_VALUE_H
#define LOGIC_NODE_VALUE_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/node_item.h>
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LogicNodeBoolEmittersChangeEvent;

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

class LOGIC_NODE_API LogicNodeBoolEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(LogicNodeBoolEmitter, flow_document::Node)

 public:
  explicit LogicNodeBoolEmitter();
  ~LogicNodeBoolEmitter() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

 protected:
  void compute() override;

 private:
  bool m_value;
};

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

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

class LOGIC_NODE_API LogicNodeBoolReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(LogicNodeBoolReceiver, flow_document::Node)

 public:
  explicit LogicNodeBoolReceiver();
  ~LogicNodeBoolReceiver() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

 protected:
  void compute() override;

 private:
  bool m_value;
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

#endif  // LOGIC_NODE_VALUE_H
