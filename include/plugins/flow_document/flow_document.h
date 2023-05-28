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
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ChangeEvent;
class Flow;

class FLOW_DOCUMENT_API FlowDocument : public egnite::Document {
  Q_OBJECT

 public:
  static std::unique_ptr<egnite::Document> create();

 public:
  ~FlowDocument() override;

  [[nodiscard]] Flow *getFlow() const;

  [[nodiscard]] Layer *getCurrentLayer() const;
  [[nodiscard]] Node *getCurrentNode() const;
  [[nodiscard]] Object *getCurrentObject() const;

  [[nodiscard]] const QList<Layer *> &getSelectedLayers() const;
  [[nodiscard]] const QList<Node *> &getSelectedNodes() const;

 public Q_SLOTS:
  void setCurrentLayer(Layer *layer);
  void setCurrentNode(Node *node);
  void setCurrentObject(Object *object);

  void switchCurrentLayer(Layer *layer);
  void switchCurrentNode(Node *node);

  void setSelectedLayers(const QList<Layer *> &layers);
  void setSelectedNodes(const QList<Node *> &nodes);

  void switchSelectedLayers(const QList<Layer *> &layers);
  void switchSelectedNodes(const QList<Node *> &nodes);

 Q_SIGNALS:
  void event(const ChangeEvent &event);

  void currentLayerChanged(Layer *layer);
  void currentNodeChanged(Node *node);
  void currentObjectChanged(Object *object);

  void selectedLayersChanged(const QList<Layer *> &layers);
  void selectedNodesChanged(const QList<Node *> &nodes);

 protected:
  explicit FlowDocument(QObject *parent = nullptr);

 private:
  std::unique_ptr<Flow> m_flow;

  Layer *m_current_layer;
  Node *m_current_node;
  Object *m_current_object;

  QList<Layer *> m_selected_layers;
  QList<Node *> m_selected_nodes;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_H
