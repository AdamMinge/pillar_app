/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document.h"

#include "flow_document/event/change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer_iterator.h"
#include "flow_document/flow/node_layer.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- FlowDocument ----------------------------- */

std::unique_ptr<egnite::Document> FlowDocument::create() {
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent),
      m_flow(std::make_unique<Flow>()),
      m_current_layer(nullptr),
      m_current_node(nullptr),
      m_current_object(nullptr) {}

FlowDocument::~FlowDocument() = default;

Flow *FlowDocument::getFlow() const { return m_flow.get(); }

Layer *FlowDocument::getCurrentLayer() const { return m_current_layer; }

Node *FlowDocument::getCurrentNode() const { return m_current_node; }

Object *FlowDocument::getCurrentObject() const { return m_current_object; }

const QList<Layer *> &FlowDocument::getSelectedLayers() const {
  return m_selected_layers;
}

const QList<Node *> &FlowDocument::getSelectedNodes() const {
  return m_selected_nodes;
}

void FlowDocument::setCurrentLayer(Layer *layer) {
  if (m_current_layer == layer) return;

  m_current_layer = layer;
  Q_EMIT currentLayerChanged(m_current_layer);

  setCurrentObject(layer);  // To remove ??
}

void FlowDocument::setCurrentNode(Node *node) {
  if (m_current_node == node) return;

  m_current_node = node;
  Q_EMIT currentNodeChanged(m_current_node);
}

void FlowDocument::setCurrentObject(Object *object) {
  if (m_current_object == object) return;

  m_current_object = object;
  Q_EMIT currentObjectChanged(m_current_object);
}

void FlowDocument::switchCurrentLayer(Layer *layer) {
  setCurrentLayer(layer);
  if (layer && !m_selected_layers.contains(layer)) setSelectedLayers({layer});
}

void FlowDocument::switchCurrentNode(Node *node) {
  setCurrentNode(node);
  if (node && !m_selected_nodes.contains(node)) setSelectedNodes({node});
}

void FlowDocument::setSelectedLayers(const QList<Layer *> &layers) {
  if (m_selected_layers == layers) return;

  m_selected_layers = layers;
  Q_EMIT selectedLayersChanged(m_selected_layers);
}

void FlowDocument::setSelectedNodes(const QList<Node *> &nodes) {
  if (m_selected_nodes == nodes) return;

  m_selected_nodes = nodes;
  Q_EMIT selectedNodesChanged(m_selected_nodes);

  auto node_layer = static_cast<NodeLayer *>(nullptr);
  for (auto node : m_selected_nodes) {
    if (!node_layer) {
      node_layer = node->getParent();
    } else if (node_layer != node->getParent()) {
      node_layer = nullptr;
      break;
    }
  }

  if (node_layer) {
    switchCurrentLayer(node_layer);
  }
}

void FlowDocument::serialize(utils::OArchive &archive) const {
  archive << utils::ArchiveProperty("flow", m_flow);
}

void FlowDocument::deserialize(utils::IArchive &archive) {
  archive >> utils::ArchiveProperty("flow", m_flow);
}

void FlowDocument::switchSelectedLayers(const QList<Layer *> &layers) {
  setSelectedLayers(layers);

  if (layers.contains(m_current_layer))
    setCurrentLayer(layers.isEmpty() ? nullptr : layers.first());
}

void FlowDocument::switchSelectedNodes(const QList<Node *> &nodes) {
  setSelectedNodes(nodes);

  if (nodes.contains(m_current_node))
    setCurrentNode(nodes.isEmpty() ? nullptr : nodes.first());
}

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] QList<Layer *> getAllLayers(FlowDocument *document,
                                          const QList<Layer *> &except) {
  auto root = document ? document->getFlow()->getRootLayer() : nullptr;
  if (!root) return {};

  auto layers = QList<Layer *>{};
  auto iter = LayerPreOrderIterator(root);
  while (iter.hasNext()) {
    if (auto layer = iter.next(); !except.contains(layer) && layer != root)
      layers.append(layer);
  }

  return layers;
}

[[nodiscard]] QList<Node *> getAllNodes(FlowDocument *document,
                                        const QList<Node *> &except) {
  auto layers = getAllLayers(document, {});
  auto nodes = QList<Node *>{};

  for (auto layer : layers) {
    if (layer->isClassOrChild<NodeLayer>()) {
      auto node_layer = static_cast<NodeLayer *>(layer);
      for (auto &node : *node_layer) {
        if (!except.contains(node.get())) nodes.append(node.get());
      }
    }
  }

  return nodes;
}

}  // namespace flow_document