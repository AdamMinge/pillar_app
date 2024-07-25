#ifndef STRING_NODE_VALUE_H
#define STRING_NODE_VALUE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- StringNodeStringEmitter ----------------------- */

class LIB_FLOW_STRING_NODE_API StringNodeStringEmitter : public Node {
  FLOW_OBJECT_CLASS(StringNodeStringEmitter, Node)

 public:
  explicit StringNodeStringEmitter();
  ~StringNodeStringEmitter() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

  void setValue(QString value);
  [[nodiscard]] QString getValue() const;

 protected:
  void compute() override;

 private:
  QString m_value;
};

/* -------------------------- StringNodeStringReceiver ---------------------- */

class LIB_FLOW_STRING_NODE_API StringNodeStringReceiver : public Node {
  FLOW_OBJECT_CLASS(StringNodeStringReceiver, Node)

 public:
  explicit StringNodeStringReceiver();
  ~StringNodeStringReceiver() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

  void setValue(QString value);
  [[nodiscard]] QString getValue() const;

 protected:
  void compute() override;

 private:
  QString m_value;
};

}  // namespace flow

#endif  // STRING_NODE_VALUE_H
