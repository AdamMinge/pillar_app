/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/node_layer.h"

#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodeLayer::NodeLayer() : Layer(LayerType::NodeLayer) {}

NodeLayer::~NodeLayer() = default;

void NodeLayer::append(std::unique_ptr<Node> node) {
  insert(m_nodes.size(), std::move(node));
}

void NodeLayer::insert(qsizetype index, std::unique_ptr<Node> node) {
  Q_ASSERT(index >= 0 && index <= m_nodes.size());
  auto insert_iter = m_nodes.begin() + index;
  auto added_node_iter = m_nodes.insert(insert_iter, std::move(node));

  (*added_node_iter)->setParent(this);
}

void NodeLayer::remove(qsizetype index) { Q_UNUSED(take(index)); }

std::unique_ptr<Node> NodeLayer::take(qsizetype index) {
  Q_ASSERT(index >= 0 && index < m_nodes.size());
  auto take_iter = m_nodes.begin() + index;
  auto node = std::move(*take_iter);
  m_nodes.erase(take_iter);

  node->setParent(nullptr);
  return node;
}

Node* NodeLayer::at(qsizetype index) const {
  Q_ASSERT(index >= 0 && index < m_nodes.size());
  return m_nodes.at(index).get();
}

qsizetype NodeLayer::indexOf(Node* node) const {
  auto iter = std::find_if(
      m_nodes.cbegin(), m_nodes.cend(),
      [node](const auto& node_ptr) { return node_ptr.get() == node; });

  if (iter != m_nodes.end()) return std::distance(m_nodes.begin(), iter);

  return -1;
}

qsizetype NodeLayer::size() const { return m_nodes.size(); }

NodeLayer::Nodes::iterator NodeLayer::begin() { return m_nodes.begin(); }

NodeLayer::Nodes::iterator NodeLayer::end() { return m_nodes.end(); }

NodeLayer::Nodes::const_iterator NodeLayer::begin() const {
  return m_nodes.begin();
}

NodeLayer::Nodes::const_iterator NodeLayer::end() const {
  return m_nodes.end();
}

std::unique_ptr<Layer> NodeLayer::clone() const {
  auto node_layer = std::make_unique<NodeLayer>();
  node_layer->init(this);
  return std::move(node_layer);
}

void NodeLayer::init(const NodeLayer* node_layer) {
  Layer::init(node_layer);

  for (const auto& node : *node_layer) {
    append(node->clone());
  }
}

}  // namespace flow_document