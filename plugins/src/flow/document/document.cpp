/* ----------------------------------- Local -------------------------------- */
#include "flow/document/document.h"

#include "flow/document/event/change_event.h"
#include "flow/document/flow/flow.h"
#include "flow/document/flow/group_layer.h"
#include "flow/document/flow/layer_iterator.h"
#include "flow/document/flow/node_layer.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/archive.h>
#include <qtils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------------------- Qtils -------------------------------- */

namespace {

template <typename LAYER, typename OBJECT>
[[nodiscard]] LAYER *getLayerByObjects(const QList<OBJECT *> &objects) {
  auto layer = static_cast<LAYER *>(nullptr);
  for (auto object : objects) {
    if (!layer) {
      layer = object->getParent();
    } else if (layer != object->getParent()) {
      layer = nullptr;
      break;
    }
  }

  return layer;
}

}  // namespace

/* ------------------------------- FlowDocument ----------------------------- */

std::unique_ptr<pillar::Document> FlowDocument::create() {
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent),
      m_flow(std::make_unique<Flow>()),
      m_current_layer(nullptr),
      m_current_node(nullptr),
      m_current_connection(nullptr),
      m_current_object(nullptr) {}

FlowDocument::~FlowDocument() = default;

Flow *FlowDocument::getFlow() const { return m_flow.get(); }

Layer *FlowDocument::getCurrentLayer() const { return m_current_layer; }

Node *FlowDocument::getCurrentNode() const { return m_current_node; }

Connection *FlowDocument::getCurrentConnection() const {
  return m_current_connection;
}

Object *FlowDocument::getCurrentObject() const { return m_current_object; }

const QList<Layer *> &FlowDocument::getSelectedLayers() const {
  return m_selected_layers;
}

const QList<Node *> &FlowDocument::getSelectedNodes() const {
  return m_selected_nodes;
}

const QList<Connection *> &FlowDocument::getSelectedConnections() const {
  return m_selected_connections;
}

const QList<Node *> &FlowDocument::getHoveredNodes() const {
  return m_hovered_nodes;
}

void FlowDocument::setCurrentLayer(Layer *layer) {
  if (m_current_layer != layer) {
    m_current_layer = layer;
    Q_EMIT currentLayerChanged(m_current_layer);
  }

  auto object = getCurrentObject();
  if (!object || object->isClassOrChild<Layer>())
    setCurrentObject(m_current_layer);
}

void FlowDocument::setCurrentNode(Node *node) {
  if (m_current_node != node) {
    m_current_node = node;
    Q_EMIT currentNodeChanged(m_current_node);
  }

  auto object = getCurrentObject();
  if (!object || object->isClassOrChild<Node>())
    setCurrentObject(m_current_node);
}

void FlowDocument::setCurrentConnection(Connection *connection) {
  if (m_current_connection != connection) {
    m_current_connection = connection;
    Q_EMIT currentConnectionChanged(m_current_connection);
  }

  auto object = getCurrentObject();
  if (!object || object->isClassOrChild<Connection>())
    setCurrentObject(m_current_connection);
}

void FlowDocument::setCurrentObject(Object *object) {
  if (m_current_object == object) return;

  m_current_object = object;
  Q_EMIT currentObjectChanged(m_current_object);
}

void FlowDocument::switchCurrentLayer(Layer *layer) {
  if (layer && !m_selected_layers.contains(layer)) setSelectedLayers({layer});
  setCurrentLayer(layer);
}

void FlowDocument::switchCurrentNode(Node *node) {
  if (node && !m_selected_nodes.contains(node)) setSelectedNodes({node});
  setCurrentNode(node);
}

void FlowDocument::switchCurrentConnection(Connection *connection) {
  if (connection && !m_selected_connections.contains(connection))
    setSelectedConnections({connection});
  setCurrentConnection(connection);
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

  if (auto node_layer = getLayerByObjects<NodeLayer>(nodes); node_layer) {
    switchCurrentLayer(node_layer);
  }
}

void FlowDocument::setSelectedConnections(
    const QList<Connection *> &connections) {
  if (m_selected_connections == connections) return;

  m_selected_connections = connections;
  Q_EMIT selectedConnectionsChanged(m_selected_connections);

  if (auto node_layer = getLayerByObjects<NodeLayer>(connections); node_layer) {
    switchCurrentLayer(node_layer);
  }
}

void FlowDocument::serialize(qtils::OArchive &archive) const {
  archive << qtils::ArchiveProperty("flow", m_flow);
}

void FlowDocument::deserialize(qtils::IArchive &archive) {
  archive >> qtils::ArchiveProperty("flow", m_flow);
}

void FlowDocument::switchSelectedLayers(const QList<Layer *> &layers) {
  setSelectedLayers(layers);

  if (!layers.contains(m_current_layer))
    setCurrentLayer(layers.isEmpty() ? nullptr : layers.first());
}

void FlowDocument::switchSelectedNodes(const QList<Node *> &nodes) {
  setSelectedNodes(nodes);

  if (!nodes.contains(m_current_node))
    setCurrentNode(nodes.isEmpty() ? nullptr : nodes.first());
}

void FlowDocument::switchSelectedConnections(
    const QList<Connection *> &connections) {
  setSelectedConnections(connections);

  if (!connections.contains(m_current_connection))
    setCurrentConnection(connections.isEmpty() ? nullptr : connections.first());
}

void FlowDocument::setHoveredNodes(const QList<Node *> &nodes) {
  if (m_hovered_nodes == nodes) return;

  m_hovered_nodes = nodes;
  Q_EMIT hoveredNodesChanged(m_hovered_nodes);
}

/* ----------------------------------- Qtils -------------------------------- */

template <>
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

      for (auto index = 0; index < node_layer->nodesCount(); ++index) {
        auto node = node_layer->nodeAt(index);
        if (!except.contains(node)) nodes.append(node);
      }
    }
  }

  return nodes;
}

[[nodiscard]] Node *findNodeById(FlowDocument *document, const QUuid &id) {
  auto nodes = getAllNodes(document);
  for (auto node : nodes) {
    if (node->getId() == id) return node;
  }

  return nullptr;
}

[[nodiscard]] QList<Connection *> getAllConnections(
    FlowDocument *document, const QList<Connection *> &except) {
  auto layers = getAllLayers(document, {});
  auto connections = QList<Connection *>{};

  for (auto layer : layers) {
    if (layer->isClassOrChild<NodeLayer>()) {
      auto node_layer = static_cast<NodeLayer *>(layer);

      for (auto index = 0; index < node_layer->connectionsCount(); ++index) {
        auto connection = node_layer->connectionAt(index);
        if (!except.contains(connection)) connections.append(connection);
      }
    }
  }

  return connections;
}

}  // namespace flow