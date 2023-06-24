/* ----------------------------------- Local -------------------------------- */
#include "flow/shape_layer.h"

#include "flow/shape.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

ShapeLayer::ShapeLayer() = default;

ShapeLayer::~ShapeLayer() = default;

void ShapeLayer::append(std::unique_ptr<Shape> shape) {
  insert(m_shapes.size(), std::move(shape));
}

void ShapeLayer::insert(qsizetype index, std::unique_ptr<Shape> shape) {
  Q_ASSERT(index >= 0 && index <= m_shapes.size());
  auto insert_iter = m_shapes.begin() + index;
  auto added_shape_iter = m_shapes.insert(insert_iter, std::move(shape));

  (*added_shape_iter)->setParent(this);
}

void ShapeLayer::remove(qsizetype index) { Q_UNUSED(take(index)); }

std::unique_ptr<Shape> ShapeLayer::take(qsizetype index) {
  Q_ASSERT(index >= 0 && index < m_shapes.size());
  auto take_iter = m_shapes.begin() + index;
  auto shape = std::move(*take_iter);
  m_shapes.erase(take_iter);

  shape->setParent(nullptr);
  return shape;
}

Shape* ShapeLayer::at(qsizetype index) const {
  Q_ASSERT(index >= 0 && index < m_shapes.size());
  return m_shapes.at(index).get();
}

qsizetype ShapeLayer::indexOf(Shape* shape) const {
  auto iter = std::find_if(
      m_shapes.cbegin(), m_shapes.cend(),
      [shape](const auto& shape_ptr) { return shape_ptr.get() == shape; });

  if (iter != m_shapes.end()) return std::distance(m_shapes.begin(), iter);

  return -1;
}

qsizetype ShapeLayer::size() const { return m_shapes.size(); }

ShapeLayer::Shapes::iterator ShapeLayer::begin() { return m_shapes.begin(); }

ShapeLayer::Shapes::iterator ShapeLayer::end() { return m_shapes.end(); }

ShapeLayer::Shapes::const_iterator ShapeLayer::begin() const {
  return m_shapes.begin();
}

ShapeLayer::Shapes::const_iterator ShapeLayer::end() const {
  return m_shapes.end();
}

std::unique_ptr<flow_document::Layer> ShapeLayer::clone() const {
  auto shape_layer = std::make_unique<ShapeLayer>();
  shape_layer->init(this);
  return std::move(shape_layer);
}

void ShapeLayer::serialize(utils::OArchive& archive) const {
  flow_document::Layer::serialize(archive);

  archive << utils::ArchiveProperty("shapes", m_shapes);
}

void ShapeLayer::deserialize(utils::IArchive& archive) {
  flow_document::Layer::deserialize(archive);

  archive >> utils::ArchiveProperty("shapes", m_shapes);
}

void ShapeLayer::init(const ShapeLayer* shape_layer) {
  flow_document::Layer::init(shape_layer);

  for (const auto& shape : *shape_layer) {
    append(shape->clone());
  }
}
