/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/add_remove_node.h"

#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- NodeEntry ------------------------------ */

NodeEntry::NodeEntry(NodeEntry&& other)
    : NodeEntry(other.node_layer, std::move(other.new_node), other.index) {}

NodeEntry::NodeEntry(NodeLayer* node_layer, qsizetype index)
    : node_layer(node_layer), new_node(nullptr), index(index) {}

NodeEntry::NodeEntry(NodeLayer* node_layer, std::unique_ptr<Node> new_node,
                     qsizetype index)
    : node_layer(node_layer), new_node(std::move(new_node)), index(index) {}

NodeEntry::~NodeEntry() = default;

/* ------------------------------ AddRemoveNodes ---------------------------- */

AddRemoveNodes::AddRemoveNodes(const QString& name, FlowDocument* document,
                               std::list<NodeEntry> entries, Command* parent)
    : egnite::Command(name, parent),
      m_document(document),
      m_entries(std::move(entries)) {
  m_entries.sort([](const auto& left, const auto& right) {
    auto left_id = getLayerHierarchicalId(left.node_layer);
    auto right_id = getLayerHierarchicalId(right.node_layer);

    if (left_id > right_id) return true;
    if (left_id == right_id && left.index > right.index) return true;

    return false;
  });
}

AddRemoveNodes::~AddRemoveNodes() = default;

void AddRemoveNodes::addNode() {
  for (auto iter = m_entries.rbegin(); iter != m_entries.rend(); ++iter) {
    auto& entry = *iter;
    Q_ASSERT(entry.new_node);

    Q_EMIT m_document->event(NodeEvent(NodeEvent::Event::AboutToBeAdded,
                                       entry.node_layer, entry.index));
    entry.node_layer->insertNode(entry.index, std::move(entry.new_node));
    Q_EMIT m_document->event(
        NodeEvent(NodeEvent::Event::Added, entry.node_layer, entry.index));
  }
}

void AddRemoveNodes::removeNode() {
  for (auto iter = m_entries.begin(); iter != m_entries.end(); ++iter) {
    auto& entry = *iter;
    Q_ASSERT(!entry.new_node);

    Q_EMIT m_document->event(NodeEvent(NodeEvent::Event::AboutToBeRemoved,
                                       entry.node_layer, entry.index));
    entry.new_node = entry.node_layer->takeNode(entry.index);
    Q_EMIT m_document->event(
        NodeEvent(NodeEvent::Event::Removed, entry.node_layer, entry.index));
  }
}

/* ---------------------------------- AddNodes ------------------------------ */

AddNodes::AddNodes(FlowDocument* document, std::list<NodeEntry> entries,
                   Command* parent)
    : AddRemoveNodes(QLatin1String("AddNodes"), document, std::move(entries),
                     parent) {
  const auto command_text =
      QObject::tr("Add Node(s)", nullptr, m_entries.size());
  setText(command_text);
}

AddNodes::~AddNodes() = default;

void AddNodes::undo() { removeNode(); }

void AddNodes::redo() { addNode(); }

/* -------------------------------- RemoveNodes ----------------------------- */

RemoveNodes::RemoveNodes(FlowDocument* document, std::list<NodeEntry> entries,
                         Command* parent)
    : AddRemoveNodes(QLatin1String("RemoveNodes"), document, std::move(entries),
                     parent) {
  const auto command_text =
      QObject::tr("Remove Node(s)", nullptr, m_entries.size());
  setText(command_text);
}

RemoveNodes::~RemoveNodes() = default;

void RemoveNodes::undo() { addNode(); }

void RemoveNodes::redo() { removeNode(); }

}  // namespace flow_document
