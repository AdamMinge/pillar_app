/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/add_remove_layer.h"

#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- LayerEntry ----------------------------- */

LayerEntry::LayerEntry(LayerEntry&& other)
    : LayerEntry(other.group_layer, std::move(other.new_layer), other.index) {}

LayerEntry::LayerEntry(GroupLayer* group_layer, qsizetype index)
    : group_layer(group_layer), new_layer(nullptr), index(index) {}

LayerEntry::LayerEntry(GroupLayer* group_layer,
                       std::unique_ptr<Layer> new_layer, qsizetype index)
    : group_layer(group_layer), new_layer(std::move(new_layer)), index(index) {}

LayerEntry::~LayerEntry() = default;

/* ------------------------------ AddRemoveLayers --------------------------- */

AddRemoveLayers::AddRemoveLayers(const QString& name, FlowDocument* document,
                                 std::list<LayerEntry> entries, Command* parent)
    : egnite::Command(name, parent),
      m_document(document),
      m_entries(std::move(entries)) {
  m_entries.sort([](const auto& left, const auto& right) {
    return left.index > right.index;
  });
}

AddRemoveLayers::~AddRemoveLayers() = default;

void AddRemoveLayers::addLayer() {
  for (auto& entry : m_entries) {
    Q_ASSERT(entry.new_layer);

    Q_EMIT m_document->event(LayerEvent(LayerEvent::Type::LayerAboutToBeAdded,
                                        entry.group_layer, entry.index));
    entry.group_layer->insert(entry.index, std::move(entry.new_layer));
    Q_EMIT m_document->event(LayerEvent(LayerEvent::Type::LayerAdded,
                                        entry.group_layer, entry.index));
  }
}

void AddRemoveLayers::removeLayer() {
  for (auto& entry : m_entries) {
    Q_ASSERT(!entry.new_layer);

    Q_EMIT m_document->event(LayerEvent(LayerEvent::Type::LayerAboutToBeRemoved,
                                        entry.group_layer, entry.index));
    entry.new_layer = entry.group_layer->take(entry.index);
    Q_EMIT m_document->event(LayerEvent(LayerEvent::Type::LayerRemoved,
                                        entry.group_layer, entry.index));
  }
}

/* ---------------------------------- AddLayers ----------------------------- */

AddLayers::AddLayers(FlowDocument* document, std::list<LayerEntry> entries,
                     Command* parent)
    : AddRemoveLayers(QLatin1String("AddLayers"), document, std::move(entries),
                      parent) {
  const auto command_text = m_entries.size() > 1 ? QObject::tr("Add Layers")
                                                 : QObject::tr("Add Layer");
  setText(command_text);
}

AddLayers::~AddLayers() = default;

void AddLayers::undo() { removeLayer(); }

void AddLayers::redo() { addLayer(); }

/* -------------------------------- RemoveLayers ---------------------------- */

RemoveLayers::RemoveLayers(FlowDocument* document,
                           std::list<LayerEntry> entries, Command* parent)
    : AddRemoveLayers(QLatin1String("RemoveLayers"), document,
                      std::move(entries), parent) {
  const auto command_text = m_entries.size() > 1 ? QObject::tr("Remove Layers")
                                                 : QObject::tr("Remove Layer");
  setText(command_text);
}

RemoveLayers::~RemoveLayers() = default;

void RemoveLayers::undo() { addLayer(); }

void RemoveLayers::redo() { removeLayer(); }

}  // namespace flow_document
