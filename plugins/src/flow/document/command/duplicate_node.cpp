/* ----------------------------------- Local -------------------------------- */
#include "flow/document/command/duplicate_node.h"

#include "flow/document/document.h"
#include "flow/document/event/node_change_event.h"
#include "flow/document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------------- DuplicateNodeData -------------------------- */

DuplicateNodeData::DuplicateNodeData(DuplicateNodeData&& other)
    : node_layer(other.node_layer),
      copy_node(std::move(other.copy_node)),
      index(other.index) {}

DuplicateNodeData::DuplicateNodeData(Node* node)
    : node_layer(node->getParent()),
      copy_node(node->clone()),
      index(node_layer->indexOfNode(node) + 1) {
  copy_node->setName(QString("%1 Copy").arg(copy_node->getName()));
}

DuplicateNodeData::~DuplicateNodeData() = default;

/* ------------------------------ DuplicateNodes ---------------------------- */

DuplicateNodes::DuplicateNodes(FlowDocument* document, QList<Node*> nodes,
                               Command* parent)
    : pillar::Command(QLatin1String("DuplicateNodes"), parent),
      m_document(document) {
  for (auto node : nodes) {
    m_duplicate_data.push_back(DuplicateNodeData(node));
  }

  m_duplicate_data.sort([](const auto& left, const auto& right) {
    auto left_id = getLayerHierarchicalId(left.node_layer);
    auto right_id = getLayerHierarchicalId(right.node_layer);

    if (left_id > right_id) return true;
    if (left_id == right_id && left.index > right.index) return true;

    return false;
  });

  const auto command_text =
      QObject::tr("Duplicate Node(s)", nullptr, m_duplicate_data.size());
  setText(command_text);
}

DuplicateNodes::~DuplicateNodes() = default;

void DuplicateNodes::undo() {
  for (auto iter = m_duplicate_data.rbegin(); iter != m_duplicate_data.rend();
       ++iter) {
    auto& data = *iter;
    Q_ASSERT(data.node_layer);
    Q_ASSERT(!data.copy_node);

    Q_EMIT m_document->event(NodeEvent(NodeEvent::Event::AboutToBeRemoved,
                                       data.node_layer, data.index));
    data.copy_node = data.node_layer->takeNode(data.index);
    Q_EMIT m_document->event(
        NodeEvent(NodeEvent::Event::Removed, data.node_layer, data.index));
  }
}

void DuplicateNodes::redo() {
  for (auto iter = m_duplicate_data.begin(); iter != m_duplicate_data.end();
       ++iter) {
    auto& data = *iter;
    Q_ASSERT(data.node_layer);
    Q_ASSERT(data.copy_node);

    Q_EMIT m_document->event(NodeEvent(NodeEvent::Event::AboutToBeAdded,
                                       data.node_layer, data.index));
    data.node_layer->insertNode(data.index, std::move(data.copy_node));
    Q_EMIT m_document->event(
        NodeEvent(NodeEvent::Event::Added, data.node_layer, data.index));
  }
}

}  // namespace flow
