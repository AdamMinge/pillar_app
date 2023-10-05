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

/* -------------------------- StringNodeStringEmitter ----------------------- */

class STRING_NODE_API StringNodeStringEmitter : public flow_document::Node {
  FLOW_OBJECT_CLASS(StringNodeStringEmitter, flow_document::Node)

 public:
  explicit StringNodeStringEmitter();
  ~StringNodeStringEmitter() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

/* -------------------------- StringNodeStringReceiver ---------------------- */

class STRING_NODE_API StringNodeStringReceiver : public flow_document::Node {
  FLOW_OBJECT_CLASS(StringNodeStringReceiver, flow_document::Node)

 public:
  explicit StringNodeStringReceiver();
  ~StringNodeStringReceiver() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

#endif  // STRING_NODE_VALUE_H
