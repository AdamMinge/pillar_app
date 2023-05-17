/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Layer::Layer(LayerType type)
    : Object(Type::Layer),
      m_type(type),
      m_parent(nullptr),
      m_opacity(0),
      m_locked(false),
      m_visible(true) {}

Layer::~Layer() = default;

Layer::LayerType Layer::getLayerType() const { return m_type; }

void Layer::setPosition(const QPointF& position) { m_position = position; }

QPointF Layer::getPosition() const { return m_position; }

qreal Layer::getOpacity() const { return m_opacity; }

void Layer::setOpacity(qreal opacity) { m_opacity = opacity; }

void Layer::setLocked(bool locked) { m_locked = locked; }

bool Layer::isLocked() const { return m_locked; }

void Layer::setVisible(bool visible) { m_visible = visible; }

bool Layer::isVisible() const { return m_visible; }

GroupLayer* Layer::getParent() const { return m_parent; }

void Layer::setParent(GroupLayer* parent) { m_parent = parent; }

}  // namespace flow_document
