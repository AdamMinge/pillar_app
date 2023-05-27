#ifndef FLOW_DOCUMENT_NODE_CHANGE_EVENT_H
#define FLOW_DOCUMENT_NODE_CHANGE_EVENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/change_event.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeLayer;
class Node;

/* --------------------------------- NodeEvent ------------------------------ */

class FLOW_DOCUMENT_API NodeEvent : public ChangeEvent {
 public:
  explicit NodeEvent(Type type, NodeLayer* node_layer, qsizetype index);
  ~NodeEvent() override;

  [[nodiscard]] NodeLayer* getNodeLayer() const;
  [[nodiscard]] qsizetype getIndex() const;
  [[nodiscard]] Node* getNode() const;

 private:
  NodeLayer* m_node_layer;
  qsizetype m_index;
};

/* ---------------------------------- NodesEvent ---------------------------- */

class FLOW_DOCUMENT_API NodesEvent : public ChangeEvent {
 public:
  explicit NodesEvent(Type type, QList<Node*> nodes);
  ~NodesEvent() override;

  [[nodiscard]] const QList<Node*>& getNodes() const;

 private:
  QList<Node*> m_nodes;
};

/* ------------------------------ NodesChangeEvent -------------------------- */

class FLOW_DOCUMENT_API NodesChangeEvent : public NodesEvent {
 public:
  enum class Property {
    Name = 1 << 0,
    Visible = 1 << 1,
    Position = 1 << 4,
    Custom = 1 << 5,
  };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit NodesChangeEvent(QList<Node*> nodes, Properties properties);
  ~NodesChangeEvent() override;

  [[nodiscard]] Properties getProperties() const;

 private:
  Properties m_properties;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_CHANGE_EVENT_H
