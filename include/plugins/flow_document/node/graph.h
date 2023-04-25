#ifndef FLOW_DOCUMENT_GRAPH_H
#define FLOW_DOCUMENT_GRAPH_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QUuid>
/* --------------------------------- Standard ------------------------------- */
#include <set>
#include <unordered_map>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/container/hash.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;
class PinConnection;

class NodeFactory;
class NodeFactories;

class FLOW_DOCUMENT_API Graph : public QObject,
                                public egnite::PluginListener<NodeFactories> {
 public:
  explicit Graph(QObject *parent = nullptr);
  ~Graph() override;

  QUuid addNode(const QString &node_type);
  bool removeNode(const QUuid &node_id);

  [[nodiscard]] const Node &getNode(const QUuid &node_id) const;
  [[nodiscard]] const Node *findNode(const QUuid &node_id) const;

  QUuid addConnection(const QUuid &out_node_id, size_t out_pin_id,
                      const QUuid &in_node_id, size_t in_pin_id);
  bool removeConnection(const QUuid &connection_id);

  [[nodiscard]] const PinConnection &getConnection(
      const QUuid &connection_id) const;
  [[nodiscard]] const PinConnection *findConnection(
      const QUuid &connection_id) const;

 protected:
  void addedObject(NodeFactories *factories) override;
  void removedObject(NodeFactories *factories) override;

 private:
  [[nodiscard]] NodeFactory *findFactory(const QString &node_type);

 private:
  std::unordered_map<QUuid, std::unique_ptr<Node>, utils::QUuidHash> m_nodes;
  std::unordered_map<QUuid, std::unique_ptr<PinConnection>, utils::QUuidHash>
      m_connections;
  std::set<NodeFactories *> m_node_factories;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GRAPH_H
