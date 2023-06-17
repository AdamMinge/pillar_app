/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/layer.h"

#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer_iterator.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Layer -------------------------------- */

Layer::Layer()
    : m_parent(nullptr), m_opacity(0), m_locked(false), m_visible(true) {}

Layer::~Layer() = default;

void Layer::setPosition(const QPointF& position) { m_position = position; }

QPointF Layer::getPosition() const { return m_position; }

qreal Layer::getOpacity() const { return m_opacity; }

void Layer::setOpacity(qreal opacity) { m_opacity = opacity; }

void Layer::setLocked(bool locked) { m_locked = locked; }

bool Layer::isLocked() const { return m_locked; }

void Layer::setVisible(bool visible) { m_visible = visible; }

bool Layer::isVisible() const { return m_visible; }

GroupLayer* Layer::getParent() const { return m_parent; }

GroupLayer* Layer::getRoot() const {
  auto root = getParent();
  while (root && root->getParent()) {
    root = root->getParent();
  }

  return root;
}

bool Layer::isParent(Layer* layer) const {
  auto root = getParent();
  while (root && root->getParent()) {
    if (root == layer) return true;
    root = root->getParent();
  }

  return false;
}

bool Layer::isParentOrSelf(Layer* layer) const {
  return layer == this || isParent(layer);
}

void Layer::init(const Layer* layer) {
  Object::init(layer);

  m_opacity = layer->m_opacity;
  m_position = layer->m_position;
  m_locked = layer->m_locked;
  m_visible = layer->m_visible;
}

void Layer::setParent(GroupLayer* parent) { m_parent = parent; }

void Layer::serialize(utils::OArchive& archive) const {
  Object::serialize(archive);

  archive << utils::ArchiveProperty("position", m_position);
  archive << utils::ArchiveProperty("opacity", m_opacity);
  archive << utils::ArchiveProperty("locked", m_locked);
  archive << utils::ArchiveProperty("visible", m_visible);
}

void Layer::deserialize(utils::IArchive& archive) {
  Object::deserialize(archive);

  archive >> utils::ArchiveProperty("position", m_position);
  archive >> utils::ArchiveProperty("opacity", m_opacity);
  archive >> utils::ArchiveProperty("locked", m_locked);
  archive >> utils::ArchiveProperty("visible", m_visible);
}

/* -------------------------------- Layer Utils ----------------------------- */

qsizetype getLayerHierarchicalId(Layer* layer) {
  auto root = layer->getRoot();
  auto id = 0;
  if (root) {
    auto iter = LayerPreOrderIterator(root);
    while (iter.hasNext() && iter.next() != layer) id += 1;
  }

  return id;
}

QList<qsizetype> getLayersHierarchicalIds(const QList<Layer*>& layers) {
  if (layers.empty()) return {};

  auto ids = QList<qsizetype>(layers.size());
  auto root = layers.at(0)->getRoot();
  auto remaining = ids.size();
  auto id = 0;

  if (root) {
    auto iter = LayerPreOrderIterator(root);
    while (iter.hasNext() && remaining > 0) {
      auto layer = iter.next();
      auto index = layers.indexOf(layer);

      if (index >= 0) {
        ids[index] = id;
        remaining -= 1;
      }

      id += 1;
    }
  }

  return remaining == 0 ? ids : QList<qsizetype>{};
}

Layer* getLayerByHierarchicalId(Layer* root, qsizetype id) {
  if (root) {
    Q_ASSERT(!root->getRoot());
    auto layer = root;
    auto iter = LayerPreOrderIterator(layer);

    id += 1;
    while (iter.hasNext() && id > 0) {
      layer = iter.next();
      id -= 1;
    }

    if (id == 0) return layer;
  }

  return nullptr;
}

QList<Layer*> getLayersByHierarchicalIds(Layer* root,
                                         const QList<qsizetype>& ids) {
  if (!root) return {};

  Q_ASSERT(!root->getRoot());
  auto layers = QList<Layer*>(ids.size());
  auto iter = LayerPreOrderIterator(root);
  auto remaining = ids.size();
  auto id = 0;

  while (iter.hasNext() && remaining > 0) {
    auto layer = iter.next();
    auto index = ids.indexOf(id);

    if (index >= 0) {
      layers[index] = layer;
      remaining -= 1;
    }

    id += 1;
  }

  return remaining == 0 ? layers : QList<Layer*>{};
}

}  // namespace flow_document
