#ifndef FLOW_DOCUMENT_FLOW_GRAPH_H
#define FLOW_DOCUMENT_FLOW_GRAPH_H

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

class FlowNode;
class FlowConnection;

class FlowNodeFactory;
class FlowNodeFactories;

class FLOW_DOCUMENT_API FlowGraph
    : public QObject,
      public egnite::PluginListener<FlowNodeFactories> {
 public:
  explicit FlowGraph(QObject *parent = nullptr);
  ~FlowGraph() override;

  QUuid addNode(const QString &node_type);
  bool removeNode(const QUuid &node_id);

  [[nodiscard]] const FlowNode &getNode(const QUuid &node_id) const;
  [[nodiscard]] const FlowNode *findNode(const QUuid &node_id) const;

  QUuid addConnection(const QUuid &out_node_id, size_t out_pin_id,
                      const QUuid &in_node_id, size_t in_pin_id);
  bool removeConnection(const QUuid &connection_id);

  [[nodiscard]] const FlowConnection &getConnection(
      const QUuid &connection_id) const;
  [[nodiscard]] const FlowConnection *findConnection(
      const QUuid &connection_id) const;

 protected:
  void addedObject(FlowNodeFactories *factories) override;
  void removedObject(FlowNodeFactories *factories) override;

 private:
  [[nodiscard]] FlowNodeFactory *findFactory(const QString &node_type);

 private:
  std::unordered_map<QUuid, std::unique_ptr<FlowNode>, utils::QUuidHash>
      m_nodes;
  std::unordered_map<QUuid, std::unique_ptr<FlowConnection>, utils::QUuidHash>
      m_connections;
  std::set<FlowNodeFactories *> m_node_factories;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_GRAPH_H
