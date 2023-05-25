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
  explicit LayerEvent(Type type, GroupLayer* group_layer, qsizetype index);
  ~LayerEvent() override;

  [[nodiscard]] GroupLayer* getGroupLayer() const;
  [[nodiscard]] qsizetype getIndex() const;
  [[nodiscard]] Layer* getLayer() const;

 private:
  GroupLayer* m_group_layer;
  qsizetype m_index;
};

/* ------------------------------ LayersChangeEvent ------------------------- */

class FLOW_DOCUMENT_API LayersEvent : public ChangeEvent {
 public:
  explicit LayersEvent(Type type, QList<Layer*> layers);
  ~LayersEvent() override;

  [[nodiscard]] const QList<Layer*>& getLayers() const;

 private:
  QList<Layer*> m_layers;
};

/* ------------------------------ LayersChangeEvent ------------------------- */

class FLOW_DOCUMENT_API LayersChangeEvent : public LayersEvent {
 public:
  enum class Property {
    Name = 1 << 0,
    Visible = 1 << 1,
    Locked = 1 << 2,
    Opacity = 1 << 3,
    Position = 1 << 4,
    Custom = 1 << 5,
  };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit LayersChangeEvent(QList<Layer*> layers, Properties properties);
  ~LayersChangeEvent() override;

  [[nodiscard]] Properties getProperties() const;

 private:
  Properties m_properties;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_CHANGE_EVENT_H
