/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

GroupLayer::GroupLayer() : Layer(LayerType::GroupLayer) {}

GroupLayer::~GroupLayer() = default;

void GroupLayer::append(std::unique_ptr<Layer> layer) {
  insert(m_layers.size(), std::move(layer));
}

void GroupLayer::insert(qsizetype index, std::unique_ptr<Layer> layer) {
  auto insert_iter = m_layers.begin() + index;
  auto added_layer_iter = m_layers.insert(insert_iter, std::move(layer));

  (*added_layer_iter)->setParent(this);
}

void GroupLayer::remove(qsizetype index) { Q_UNUSED(take(index)); }

std::unique_ptr<Layer> GroupLayer::take(qsizetype index) {
  auto take_iter = m_layers.begin() + index;
  auto layer = std::move(*take_iter);
  m_layers.erase(take_iter);

  layer->setParent(nullptr);
  return layer;
}

Layer* GroupLayer::at(qsizetype index) const {
  return m_layers.at(index).get();
}

qsizetype GroupLayer::indexOf(Layer* layer) const {
  auto iter = std::find_if(
      m_layers.cbegin(), m_layers.cend(),
      [layer](const auto& layer_ptr) { return layer_ptr.get() == layer; });

  if (iter != m_layers.end()) return std::distance(m_layers.begin(), iter);

  return -1;
}

qsizetype GroupLayer::size() const { return m_layers.size(); }

GroupLayer::Layers::iterator GroupLayer::begin() { return m_layers.begin(); }

GroupLayer::Layers::iterator GroupLayer::end() { return m_layers.end(); }

GroupLayer::Layers::const_iterator GroupLayer::begin() const {
  return m_layers.begin();
}

GroupLayer::Layers::const_iterator GroupLayer::end() const {
  return m_layers.end();
}

}  // namespace flow_document
