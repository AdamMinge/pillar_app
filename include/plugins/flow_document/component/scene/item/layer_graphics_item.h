#ifndef FLOW_DOCUMENT_LAYER_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_LAYER_GRAPHICS_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_graphics_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Layer;
class GroupLayer;
class NodeLayer;
class NodeGraphicsItem;
class LayersChangeEvent;

/* ----------------------------- LayerGraphicsItem -------------------------- */

class FLOW_DOCUMENT_API LayerGraphicsItem : public ObjectGraphicsItem {
  Q_OBJECT

 public:
  explicit LayerGraphicsItem(Layer* layer, FlowDocument* document,
                             QGraphicsItem* parent = nullptr);
  ~LayerGraphicsItem() override;

  [[nodiscard]] Layer* getLayer() const;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;
  void onUpdate(const LayersChangeEvent& event);
};

/* -------------------------- GroupLayerGraphicsItem ------------------------ */

class FLOW_DOCUMENT_API GroupLayerGraphicsItem : public LayerGraphicsItem {
  Q_OBJECT

 public:
  explicit GroupLayerGraphicsItem(GroupLayer* layer, FlowDocument* document,
                                  QGraphicsItem* parent = nullptr);
  ~GroupLayerGraphicsItem() override;

  [[nodiscard]] GroupLayer* getGroupLayer() const;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 private:
  QList<LayerGraphicsItem*> m_layer_items;
};

/* --------------------------- NodeLayerGraphicsItem ------------------------ */

class FLOW_DOCUMENT_API NodeLayerGraphicsItem : public LayerGraphicsItem {
  Q_OBJECT

 public:
  explicit NodeLayerGraphicsItem(NodeLayer* layer, FlowDocument* document,
                                 QGraphicsItem* parent = nullptr);
  ~NodeLayerGraphicsItem() override;

  [[nodiscard]] NodeLayer* getNodeLayer() const;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 private:
  QList<NodeGraphicsItem*> m_node_items;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_GRAPHICS_ITEM_H
