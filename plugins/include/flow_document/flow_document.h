#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/document/document.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ChangeEvent;
class Flow;

/* ------------------------------- FlowDocument ----------------------------- */

class FLOW_DOCUMENT_API FlowDocument : public egnite::Document {
  Q_OBJECT

 public:
  static std::unique_ptr<egnite::Document> create();

 public:
  ~FlowDocument() override;

  [[nodiscard]] Flow *getFlow() const;

  [[nodiscard]] Layer *getCurrentLayer() const;
  [[nodiscard]] Node *getCurrentNode() const;
  [[nodiscard]] Connection *getCurrentConnection() const;
  [[nodiscard]] Object *getCurrentObject() const;

  [[nodiscard]] const QList<Layer *> &getSelectedLayers() const;
  [[nodiscard]] const QList<Node *> &getSelectedNodes() const;
  [[nodiscard]] const QList<Connection *> &getSelectedConnections() const;

  [[nodiscard]] const QList<Node *> &getHoveredNodes() const;

  void serialize(qtils::OArchive &archive) const override;
  void deserialize(qtils::IArchive &archive) override;

 public Q_SLOTS:
  void setCurrentLayer(Layer *layer);
  void setCurrentNode(Node *node);
  void setCurrentConnection(Connection *connection);
  void setCurrentObject(Object *object);

  void switchCurrentLayer(Layer *layer);
  void switchCurrentNode(Node *node);
  void switchCurrentConnection(Connection *connection);

  void setSelectedLayers(const QList<Layer *> &layers);
  void setSelectedNodes(const QList<Node *> &nodes);
  void setSelectedConnections(const QList<Connection *> &connections);

  void switchSelectedLayers(const QList<Layer *> &layers);
  void switchSelectedNodes(const QList<Node *> &nodes);
  void switchSelectedConnections(const QList<Connection *> &connections);

  void setHoveredNodes(const QList<Node *> &nodes);

 Q_SIGNALS:
  void event(const ChangeEvent &event);

  void currentLayerChanged(Layer *layer);
  void currentNodeChanged(Node *node);
  void currentConnectionChanged(Connection *connection);
  void currentObjectChanged(Object *object);

  void selectedLayersChanged(const QList<Layer *> &layers);
  void selectedNodesChanged(const QList<Node *> &nodes);
  void selectedConnectionsChanged(const QList<Connection *> &connections);

  void hoveredNodesChanged(const QList<Node *> &nodes);

 protected:
  explicit FlowDocument(QObject *parent = nullptr);

 private:
  std::unique_ptr<Flow> m_flow;

  Layer *m_current_layer;
  Node *m_current_node;
  Connection *m_current_connection;
  Object *m_current_object;

  QList<Layer *> m_selected_layers;
  QList<Node *> m_selected_nodes;
  QList<Connection *> m_selected_connections;

  QList<Node *> m_hovered_nodes;
};

/* ----------------------------------- Qtils -------------------------------- */

template <typename LAYER = Layer>
[[nodiscard]] QList<LAYER *> getAllLayers(FlowDocument *document,
                                          const QList<LAYER *> &except = {}) {
  auto layers = QList<LAYER *>{};
  for (Layer *layer : getAllLayers<Layer>(document)) {
    if (layer->isClassOrChild<LAYER>()) {
      layers.append(static_cast<LAYER *>(layer));
    }
  }

  return layers;
}

template <>
[[nodiscard]] QList<Layer *> getAllLayers(FlowDocument *document,
                                          const QList<Layer *> &except);

[[nodiscard]] QList<Node *> getAllNodes(FlowDocument *document,
                                        const QList<Node *> &except = {});

[[nodiscard]] Node *findNodeById(FlowDocument *document, const QUuid &id);

[[nodiscard]] QList<Connection *> getAllConnections(
    FlowDocument *document, const QList<Connection *> &except = {});

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_H
