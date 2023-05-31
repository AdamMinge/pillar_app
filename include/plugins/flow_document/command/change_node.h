#ifndef FLOW_DOCUMENT_CHANGE_NODE_H
#define FLOW_DOCUMENT_CHANGE_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_value.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Node;

/* ------------------------------ SetNodesVisible --------------------------- */

class FLOW_DOCUMENT_API SetNodesVisible : public ChangeValue<Node, bool> {
 public:
  explicit SetNodesVisible(FlowDocument* document, QList<Node*> nodes,
                           bool visible, Command* parent = nullptr);
  ~SetNodesVisible() override;

 protected:
  [[nodiscard]] bool getValue(const Node* node) const override;
  void setValue(Node* node, const bool& visible) override;
};

/* ------------------------------- SetNodesName ----------------------------- */

class FLOW_DOCUMENT_API SetNodesName : public ChangeValue<Node, QString> {
 public:
  explicit SetNodesName(FlowDocument* document, QList<Node*> nodes,
                        QString name, Command* parent = nullptr);
  ~SetNodesName() override;

 protected:
  [[nodiscard]] QString getValue(const Node* node) const override;
  void setValue(Node* node, const QString& name) override;
};

/* ------------------------------ SetNodesPosition -------------------------- */

class FLOW_DOCUMENT_API SetNodesPosition : public ChangeValue<Node, QPointF> {
 public:
  explicit SetNodesPosition(FlowDocument* document, QList<Node*> nodes,
                            QPointF position, Command* parent = nullptr);
  ~SetNodesPosition() override;

 protected:
  [[nodiscard]] QPointF getValue(const Node* node) const override;
  void setValue(Node* node, const QPointF& position) override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_NODE_H