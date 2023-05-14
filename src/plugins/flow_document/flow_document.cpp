/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document.h"

#include "flow_document/flow/flow.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

std::unique_ptr<egnite::Document> FlowDocument::create() {
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent),
      m_flow(std::make_unique<Flow>()),
      m_current_layer(nullptr) {}

FlowDocument::~FlowDocument() = default;

Flow *FlowDocument::getFlow() const { return m_flow.get(); }

Layer *FlowDocument::getCurrentLayer() const { return m_current_layer; }

const QList<Layer *> &FlowDocument::getSelectedLayers() const {
  return m_selected_layers;
}

const QList<Object *> &FlowDocument::getSelectedObject() const {
  return m_selected_objects;
}

void FlowDocument::setCurrentLayer(Layer *layer) {
  if (m_current_layer == layer) return;

  m_current_layer = layer;
  Q_EMIT currentLayerChanged(m_current_layer);
}

void FlowDocument::setSelectedLayers(const QList<Layer *> &layers) {
  if (m_selected_layers != layers) return;

  m_selected_layers = layers;
  Q_EMIT selectedLayersChanged(m_selected_layers);
}

void FlowDocument::setSelectedObjects(const QList<Object *> &objects) {
  if (m_selected_objects != objects) return;

  m_selected_objects = objects;
  Q_EMIT selectedObjectsChanged(m_selected_objects);
}

}  // namespace flow_document