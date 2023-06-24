#ifndef SHAPE_LAYER_H
#define SHAPE_LAYER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/layer.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class Shape;

class SHAPE_API ShapeLayer : public flow_document::Layer {
  FLOW_OBJECT_CLASS(ShapeLayer, flow_document::Layer)

 public:
  using Shapes = std::vector<std::unique_ptr<Shape>>;

 public:
  explicit ShapeLayer();
  ~ShapeLayer() override;

  void append(std::unique_ptr<Shape> shape);
  void insert(qsizetype index, std::unique_ptr<Shape> shape);
  void remove(qsizetype index);

  [[nodiscard]] std::unique_ptr<Shape> take(qsizetype index);
  [[nodiscard]] Shape* at(qsizetype index) const;
  [[nodiscard]] qsizetype indexOf(Shape* shape) const;

  [[nodiscard]] qsizetype size() const;

  Shapes::iterator begin();
  Shapes::iterator end();

  Shapes::const_iterator begin() const;
  Shapes::const_iterator end() const;

  [[nodiscard]] std::unique_ptr<flow_document::Layer> clone() const override;

  void serialize(utils::OArchive& archive) const override;
  void deserialize(utils::IArchive& archive) override;

 protected:
  void init(const ShapeLayer* shape_layer);

 private:
  Shapes m_shapes;
};

#endif  // SHAPE_LAYER_H
