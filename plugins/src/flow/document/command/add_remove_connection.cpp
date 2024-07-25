/* ----------------------------------- Local -------------------------------- */
#include "flow/document/command/add_remove_connection.h"

#include "flow/document/document.h"
#include "flow/document/event/connection_change_event.h"
#include "flow/document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------ ConnectionEntry --------------------------- */

ConnectionEntry::ConnectionEntry(ConnectionEntry&& other)
    : ConnectionEntry(other.node_layer, std::move(other.new_connection),
                      other.index) {}

ConnectionEntry::ConnectionEntry(NodeLayer* node_layer, qsizetype index)
    : node_layer(node_layer), new_connection(nullptr), index(index) {}

ConnectionEntry::ConnectionEntry(NodeLayer* node_layer,
                                 std::unique_ptr<Connection> new_connection,
                                 qsizetype index)
    : node_layer(node_layer),
      new_connection(std::move(new_connection)),
      index(index) {}

ConnectionEntry::~ConnectionEntry() = default;

/* ---------------------------- AddRemoveConnections ------------------------ */

AddRemoveConnections::AddRemoveConnections(const QString& name,
                                           FlowDocument* document,
                                           std::list<ConnectionEntry> entries,
                                           Command* parent)
    : pillar::Command(name, parent),
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

AddRemoveConnections::~AddRemoveConnections() = default;

void AddRemoveConnections::addConnection() {
  for (auto iter = m_entries.rbegin(); iter != m_entries.rend(); ++iter) {
    auto& entry = *iter;
    Q_ASSERT(entry.new_connection);

    Q_EMIT m_document->event(ConnectionEvent(
        ConnectionEvent::Event::AboutToBeAdded, entry.node_layer, entry.index));
    entry.node_layer->insertConnection(entry.index,
                                       std::move(entry.new_connection));
    Q_EMIT m_document->event(ConnectionEvent(ConnectionEvent::Event::Added,
                                             entry.node_layer, entry.index));
  }
}

void AddRemoveConnections::removeConnection() {
  for (auto iter = m_entries.begin(); iter != m_entries.end(); ++iter) {
    auto& entry = *iter;
    Q_ASSERT(!entry.new_connection);

    Q_EMIT m_document->event(
        ConnectionEvent(ConnectionEvent::Event::AboutToBeRemoved,
                        entry.node_layer, entry.index));
    entry.new_connection = entry.node_layer->takeConnection(entry.index);
    Q_EMIT m_document->event(ConnectionEvent(ConnectionEvent::Event::Removed,
                                             entry.node_layer, entry.index));
  }
}

/* ------------------------------- AddConnections --------------------------- */

AddConnections::AddConnections(FlowDocument* document,
                               std::list<ConnectionEntry> entries,
                               Command* parent)
    : AddRemoveConnections(QLatin1String("AddConnections"), document,
                           std::move(entries), parent) {
  const auto command_text =
      QObject::tr("Add Connection(s)", nullptr, m_entries.size());
  setText(command_text);
}

AddConnections::~AddConnections() = default;

void AddConnections::undo() { removeConnection(); }

void AddConnections::redo() { addConnection(); }

/* ------------------------------ RemoveConnections ------------------------- */

RemoveConnections::RemoveConnections(FlowDocument* document,
                                     std::list<ConnectionEntry> entries,
                                     Command* parent)
    : AddRemoveConnections(QLatin1String("RemoveConnections"), document,
                           std::move(entries), parent) {
  const auto command_text =
      QObject::tr("Remove Connection(s)", nullptr, m_entries.size());
  setText(command_text);
}

RemoveConnections::~RemoveConnections() = default;

void RemoveConnections::undo() { addConnection(); }

void RemoveConnections::redo() { removeConnection(); }

}  // namespace flow
