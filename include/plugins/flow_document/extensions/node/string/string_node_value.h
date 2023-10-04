#ifndef STRING_NODE_VALUE_H
#define STRING_NODE_VALUE_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLineEdit>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- StringNodeValueEmitter ------------------------ */

class STRING_NODE_API StringNodeValueEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(StringNodeValueEmitter, flow_document::Node)

 public:
  explicit StringNodeValueEmitter();
  ~StringNodeValueEmitter() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

/* -------------------------- StringNodeValueReceiver ----------------------- */

class STRING_NODE_API StringNodeValueReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(StringNodeValueReceiver, flow_document::Node)

 public:
  explicit StringNodeValueReceiver();
  ~StringNodeValueReceiver() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

#endif  // STRING_NODE_VALUE_H
