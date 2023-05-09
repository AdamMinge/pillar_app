#ifndef FLOW_DOCUMENT_LAYER_H
#define FLOW_DOCUMENT_LAYER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupLayer;

class FLOW_DOCUMENT_API Layer : public Object {
  friend GroupLayer;

  FLOW_OBJECT_CLASS(Layer, Object)

 public:
  enum class Type {
    GroupLayer,
    NodeLayer,
  };

 public:
  explicit Layer(Type type);
  ~Layer() override;

  [[nodiscard]] Type getType() const;

  void setOpacity(qreal opacity);
  [[nodiscard]] qreal getOpacity() const;

  void setLocked(bool locked);
  [[nodiscard]] bool isLocked() const;

  void setVisible(bool visible);
  bool isVisible() const;

  [[nodiscard]] GroupLayer* getParent() const;

 protected:
  void setParent(GroupLayer* parent);

 private:
  Type m_type;
  GroupLayer* m_parent;
  qreal m_opacity;
  bool m_locked;
  bool m_visible;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_H