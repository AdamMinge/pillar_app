/* ----------------------------------- Local -------------------------------- */
#include "flow/shape.h"
/* -------------------------------------------------------------------------- */

Shape::Shape() : m_parent(nullptr) {}

Shape::~Shape() = default;

ShapeLayer *Shape::getParent() const { return m_parent; }

std::unique_ptr<Shape> Shape::clone() const {
  auto shape = std::make_unique<Shape>();
  shape->init(this);
  return std::move(shape);
}

void Shape::setParent(ShapeLayer *parent) { m_parent = parent; }
