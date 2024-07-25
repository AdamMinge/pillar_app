/* ----------------------------------- Local -------------------------------- */
#include "flow/document/flow/layer_iterator.h"

#include "flow/document/flow/group_layer.h"
#include "flow/document/flow/layer.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------- LayerPostOrderIterator ----------------------- */

LayerPostOrderIterator::LayerPostOrderIterator(Layer* root) {
  m_stack.push(root);
}

LayerPostOrderIterator::~LayerPostOrderIterator() = default;

bool LayerPostOrderIterator::hasNext() const { return !m_stack.isEmpty(); }

Layer* LayerPostOrderIterator::next() {
  if (!hasNext()) return nullptr;

  auto layer = m_stack.top();

  if (layer->isClassOrChild<GroupLayer>()) {
    auto group_layer = static_cast<GroupLayer*>(layer);
    for (auto& child_layer : *group_layer) m_stack.push(child_layer.get());
  }

  m_stack.pop();

  return layer;
}

/* --------------------------- LayerPreOrderIterator ------------------------ */

LayerPreOrderIterator::LayerPreOrderIterator(Layer* root) {
  m_stack.push(root);
}

LayerPreOrderIterator::~LayerPreOrderIterator() = default;

bool LayerPreOrderIterator::hasNext() const { return !m_stack.isEmpty(); }

Layer* LayerPreOrderIterator::next() {
  if (!hasNext()) return nullptr;

  auto layer = m_stack.pop();

  if (layer->isClassOrChild<GroupLayer>()) {
    auto group_layer = static_cast<GroupLayer*>(layer);
    for (auto& child_layer : *group_layer) m_stack.push(child_layer.get());
  }

  return layer;
}

}  // namespace flow
