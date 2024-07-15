#ifndef LOGIC_NODE_VALUE_H
#define LOGIC_NODE_VALUE_H

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

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

 protected:
  void compute() override;

 private:
  bool m_value;
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

#endif  // LOGIC_NODE_VALUE_H
