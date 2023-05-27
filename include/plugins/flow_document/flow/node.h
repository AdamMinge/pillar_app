#ifndef FLOW_DOCUMENT_NODE_H
#define FLOW_DOCUMENT_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
#include "flow_document/flow/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeLayer;

class FLOW_DOCUMENT_API Node : public Object {
  friend NodeLayer;

  FLOW_OBJECT_CLASS(Node, Object)

 public:
  explicit Node();
  ~Node() override;

  void setVisible(bool visible);
  [[nodiscard]] bool isVisible() const;

  void setPosition(const QPointF &position);
  [[nodiscard]] QPointF getPosition() const;

  [[nodiscard]] size_t getPinsCounts(Pin::Type type) const;

  [[nodiscard]] const Pin &getPin(Pin::Type type, size_t index) const;
  [[nodiscard]] Pin &getPin(Pin::Type type, size_t index);

  void insertPin(Pin::Type type, Pin pin, size_t index);
  void removePin(Pin::Type type, size_t index);

  [[nodiscard]] NodeLayer *getParent() const;

  [[nodiscard]] virtual std::unique_ptr<Node> clone() const = 0;

 protected:
  virtual void compute() = 0;

  void init(const Node *node);
  void setParent(NodeLayer *parent);

 private:
  [[nodiscard]] QVector<Pin> &getPins(Pin::Type type);
  [[nodiscard]] const QVector<Pin> &getPins(Pin::Type type) const;

 private:
  NodeLayer *m_parent;
  QPointF m_position;
  QVector<Pin> m_out_pins;
  QVector<Pin> m_in_pins;
  bool m_visible;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_H