#ifndef STRING_NODE_VALUE_H
#define STRING_NODE_VALUE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

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

#endif  // STRING_NODE_VALUE_H
