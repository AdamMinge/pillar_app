#ifndef LOGIC_NODE_VALUE_H
#define LOGIC_NODE_VALUE_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- LogicNodeValueEmitter ------------------------- */

class LOGIC_NODE_API LogicNodeValueEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(LogicNodeValueEmitter, flow_document::Node)

 public:
  explicit LogicNodeValueEmitter();
  ~LogicNodeValueEmitter() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QCheckBox> m_widget;
};

/* -------------------------- LogicNodeValueReceiver ------------------------ */

class LOGIC_NODE_API LogicNodeValueReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(LogicNodeValueReceiver, flow_document::Node)

 public:
  explicit LogicNodeValueReceiver();
  ~LogicNodeValueReceiver() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QCheckBox> m_widget;
};

#endif  // LOGIC_NODE_VALUE_H
