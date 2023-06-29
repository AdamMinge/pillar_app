/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/duplicate_layer.h"

#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- DuplicateData ---------------------------- */

DuplicateData::DuplicateData(DuplicateData&& other)
    : group_layer(other.group_layer),
      copy_layer(std::move(other.copy_layer)),
      index(other.index) {}

DuplicateData::DuplicateData(Layer* layer)
    : group_layer(layer->getParent()),
      copy_layer(layer->clone()),
      index(group_layer->indexOf(layer) + 1) {
  copy_layer->setName(QString("%1 Copy").arg(copy_layer->getName()));
}

DuplicateData::~DuplicateData() = default;

/* ------------------------------ DuplicateLayers --------------------------- */

DuplicateLayers::DuplicateLayers(FlowDocument* document, QList<Layer*> layers,
                                 Command* parent)
    : egnite::Command(QLatin1String("DuplicateLayers"), parent),
      m_document(document) {
  for (auto layer : layers) {
    m_duplicate_data.push_back(DuplicateData(layer));
  }

  m_duplicate_data.sort([](const auto& left, const auto& right) {
    auto left_id = getLayerHierarchicalId(left.group_layer);
    auto right_id = getLayerHierarchicalId(right.group_layer);

    if (left_id > right_id) return true;
    if (left_id == right_id && left.index > right.index) return true;

    return false;
  });

  const auto command_text =
      QObject::tr("Duplicate Layer(s)", nullptr, m_duplicate_data.size());
  setText(command_text);
}

DuplicateLayers::~DuplicateLayers() = default;

void DuplicateLayers::undo() {
  for (auto iter = m_duplicate_data.rbegin(); iter != m_duplicate_data.rend();
       ++iter) {
    auto& data = *iter;
    Q_ASSERT(data.group_layer);
    Q_ASSERT(!data.copy_layer);

    Q_EMIT m_document->event(LayerEvent(LayerEvent::Event::AboutToBeRemoved,
                                        data.group_layer, data.index));
    data.copy_layer = data.group_layer->take(data.index);
    Q_EMIT m_document->event(
        LayerEvent(LayerEvent::Event::Removed, data.group_layer, data.index));
  }
}

void DuplicateLayers::redo() {
  for (auto iter = m_duplicate_data.begin(); iter != m_duplicate_data.end();
       ++iter) {
    auto& data = *iter;
    Q_ASSERT(data.group_layer);
    Q_ASSERT(data.copy_layer);

    Q_EMIT m_document->event(LayerEvent(LayerEvent::Event::AboutToBeAdded,
                                        data.group_layer, data.index));
    data.group_layer->insert(data.index, std::move(data.copy_layer));
    Q_EMIT m_document->event(
        LayerEvent(LayerEvent::Event::Added, data.group_layer, data.index));
  }
}

}  // namespace flow_document
