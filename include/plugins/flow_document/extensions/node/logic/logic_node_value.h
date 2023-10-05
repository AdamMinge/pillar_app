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

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

class LOGIC_NODE_API LogicNodeBoolEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(LogicNodeBoolEmitter, flow_document::Node)

 public:
  explicit LogicNodeBoolEmitter();
  ~LogicNodeBoolEmitter() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QCheckBox> m_widget;
};

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

class LOGIC_NODE_API LogicNodeBoolReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(LogicNodeBoolReceiver, flow_document::Node)

 public:
  explicit LogicNodeBoolReceiver();
  ~LogicNodeBoolReceiver() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QCheckBox> m_widget;
};

#endif  // LOGIC_NODE_VALUE_H
