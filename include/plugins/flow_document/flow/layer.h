#ifndef FLOW_DOCUMENT_LAYER_H
#define FLOW_DOCUMENT_LAYER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupLayer;

/* ----------------------------------- Layer -------------------------------- */

class FLOW_DOCUMENT_API Layer : public Object {
  friend GroupLayer;

  FLOW_OBJECT_CLASS(Layer, Object)

 public:
  enum class LayerType {
    GroupLayer,
    NodeLayer,
  };

 public:
  explicit Layer(LayerType type);
  ~Layer() override;

  [[nodiscard]] LayerType getLayerType() const;

  void setPosition(const QPointF& position);
  [[nodiscard]] QPointF getPosition() const;

  void setOpacity(qreal opacity);
  [[nodiscard]] qreal getOpacity() const;

  void setLocked(bool locked);
  [[nodiscard]] bool isLocked() const;

  void setVisible(bool visible);
  bool isVisible() const;

  [[nodiscard]] GroupLayer* getParent() const;
  [[nodiscard]] GroupLayer* getRoot() const;

  [[nodiscard]] bool isParent(Layer* layer) const;
  [[nodiscard]] bool isParentOrSelf(Layer* layer) const;

  [[nodiscard]] virtual std::unique_ptr<Layer> clone() const = 0;

 protected:
  void init(const Layer* layer);
  void setParent(GroupLayer* parent);

 private:
  LayerType m_type;
  GroupLayer* m_parent;
  QPointF m_position;
  qreal m_opacity;
  bool m_locked;
  bool m_visible;
};

/* -------------------------------- Layer Utils ----------------------------- */

[[nodiscard]] qsizetype getLayerHierarchicalId(Layer* layer);
[[nodiscard]] QList<qsizetype> getLayersHierarchicalIds(
    const QList<Layer*>& layers);

[[nodiscard]] Layer* getLayerByHierarchicalId(Layer* root, qsizetype id);
[[nodiscard]] QList<Layer*> getLayersByHierarchicalIds(
    Layer* root, const QList<qsizetype>& ids);

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_H