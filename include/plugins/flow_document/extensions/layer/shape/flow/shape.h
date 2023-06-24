#ifndef SHAPE_H
#define SHAPE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/object.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class ShapeLayer;

class SHAPE_API Shape : public flow_document::Object {
  friend ShapeLayer;

  FLOW_OBJECT_CLASS(Shape, flow_document::Object)

 public:
  explicit Shape();
  ~Shape() override;

  [[nodiscard]] ShapeLayer *getParent() const;
  [[nodiscard]] std::unique_ptr<Shape> clone() const;

 protected:
  void setParent(ShapeLayer *parent);

 private:
  ShapeLayer *m_parent;
};

#endif  // SHAPE_H
