#ifndef FLOW_DOCUMENT_LAYER_CHANGE_EVENT_H
#define FLOW_DOCUMENT_LAYER_CHANGE_EVENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/change_event.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupLayer;
class Layer;

/* --------------------------------- LayerEvent ----------------------------- */

class FLOW_DOCUMENT_API LayerEvent : public ChangeEvent {
 public:
  static constexpr QLatin1String type = QLatin1String("LayerEvent");

  enum class Event {
    AboutToBeAdded,
    Added,
    Removed,
    AboutToBeRemoved,
  };

 public:
  explicit LayerEvent(Event event, GroupLayer* group_layer, qsizetype index);
  ~LayerEvent() override;

  [[nodiscard]] Event getEvent() const;
  [[nodiscard]] GroupLayer* getGroupLayer() const;
  [[nodiscard]] qsizetype getIndex() const;

 private:
  Event m_event;
  GroupLayer* m_group_layer;
  qsizetype m_index;
};

/* ------------------------------ LayersChangeEvent ------------------------- */

class FLOW_DOCUMENT_API LayersChangeEvent : public ChangeEvent {
 public:
  static constexpr QLatin1String type = QLatin1String("LayersChangeEvent");

  enum Property : int64_t {
    Name = 1 << 0,
    Visible = 1 << 1,
    Locked = 1 << 2,
    Opacity = 1 << 3,
    Position = 1 << 4,
    Custom = 1 << 5,
  };

 public:
  explicit LayersChangeEvent(QList<Layer*> layers, Property properties);
  ~LayersChangeEvent() override;

  [[nodiscard]] const QList<Layer*>& getLayers() const;
  [[nodiscard]] Property getProperties() const;

  [[nodiscard]] bool contains(Layer* layer) const;

 private:
  QList<Layer*> m_layers;
  Property m_properties;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_CHANGE_EVENT_H
