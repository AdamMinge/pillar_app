#ifndef FLOW_DOCUMENT_NODE_LAYER_H
#define FLOW_DOCUMENT_NODE_LAYER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
#include "flow/document/flow/connection.h"
#include "flow/document/flow/layer.h"
#include "flow/document/flow/node.h"
#include "flow/document/flow/pin.h"
#include "flow/document/flow/serialization/object_unique_ptr.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API NodeLayer : public Layer {
  FLOW_OBJECT_CLASS(NodeLayer, Layer)

 public:
  using Nodes = std::vector<DynamicObjectUniquePtr<Node>>;
  using Connections = std::vector<StaticObjectUniquePtr<Connection>>;

 public:
  explicit NodeLayer();
  ~NodeLayer() override;

  void appendNode(std::unique_ptr<Node> node);
  void insertNode(qsizetype index, std::unique_ptr<Node> node);
  void removeNode(qsizetype index);
  [[nodiscard]] std::unique_ptr<Node> takeNode(qsizetype index);
  [[nodiscard]] Node* nodeAt(qsizetype index) const;
  [[nodiscard]] qsizetype indexOfNode(Node* node) const;
  [[nodiscard]] qsizetype nodesCount() const;

  void appendConnection(std::unique_ptr<Connection> connection);
  void insertConnection(qsizetype index,
                        std::unique_ptr<Connection> connection);
  void removeConnection(qsizetype index);
  [[nodiscard]] std::unique_ptr<Connection> takeConnection(qsizetype index);
  [[nodiscard]] Connection* connectionAt(qsizetype index) const;
  [[nodiscard]] qsizetype indexOfConnection(Connection* connection) const;
  [[nodiscard]] qsizetype connectionsCount() const;

  [[nodiscard]] bool canConnect(const ConnectionSide& input,
                                Pin::Type type) const;
  [[nodiscard]] bool canConnect(const ConnectionSide& output,
                                const ConnectionSide& input) const;

  [[nodiscard]] QList<Connection*> getNodeConnections(Node* node) const;
  [[nodiscard]] QList<Node*> getConnectionNodes(Connection* connection) const;

  [[nodiscard]] std::unique_ptr<Layer> clone() const override;

  void serialize(qtils::OArchive& archive) const override;
  void deserialize(qtils::IArchive& archive) override;

 protected:
  void init(const NodeLayer* node_layer);

 private:
  void makeConnection(Connection* connection);
  void terminateConnection(Connection* connection);

 private:
  Nodes m_nodes;
  Connections m_connections;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODE_LAYER_H