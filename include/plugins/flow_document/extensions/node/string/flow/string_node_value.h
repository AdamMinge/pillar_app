#ifndef STRING_NODE_VALUE_H
#define STRING_NODE_VALUE_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLineEdit>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/node_item.h>
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class StringNodeStringEmittersChangeEvent;

/* -------------------------- StringNodeStringEmitter ----------------------- */

class STRING_NODE_API StringNodeStringEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(StringNodeStringEmitter, flow_document::Node)

 public:
  explicit StringNodeStringEmitter();
  ~StringNodeStringEmitter() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(QString value);
  [[nodiscard]] QString getValue() const;

 protected:
  void compute() override;

 private:
  QString m_value;
};

/* ------------------------ StringNodeStringEmitterItem --------------------- */

class STRING_NODE_API StringNodeStringEmitterItem
    : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit StringNodeStringEmitterItem(flow_document::Node *node,
                                       flow_document::FlowDocument *document,
                                       QGraphicsItem *parent);
  ~StringNodeStringEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent &event) override;
  void onUpdate(const StringNodeStringEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QLineEdit> m_widget;
  bool m_updating;
};

/* -------------------------- StringNodeStringReceiver ---------------------- */

class STRING_NODE_API StringNodeStringReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(StringNodeStringReceiver, flow_document::Node)

 public:
  explicit StringNodeStringReceiver();
  ~StringNodeStringReceiver() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(QString value);
  [[nodiscard]] QString getValue() const;

 protected:
  void compute() override;

 private:
  QString m_value;
};

/* ------------------------ StringNodeStringReceiverItem -------------------- */

class STRING_NODE_API StringNodeStringReceiverItem
    : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit StringNodeStringReceiverItem(flow_document::Node *node,
                                        flow_document::FlowDocument *document,
                                        QGraphicsItem *parent);
  ~StringNodeStringReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

#endif  // STRING_NODE_VALUE_H
