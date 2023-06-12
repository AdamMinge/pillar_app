#ifndef FLOW_DOCUMENT_GROUP_LAYER_H
#define FLOW_DOCUMENT_GROUP_LAYER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API GroupLayer : public Layer {
  FLOW_OBJECT_CLASS(GroupLayer, Layer)

 public:
  using Layers = std::vector<std::unique_ptr<Layer>>;

 public:
  explicit GroupLayer();
  ~GroupLayer() override;

  void append(std::unique_ptr<Layer> layer);
  void insert(qsizetype index, std::unique_ptr<Layer> layer);
  void remove(qsizetype index);

  [[nodiscard]] std::unique_ptr<Layer> take(qsizetype index);
  [[nodiscard]] Layer* at(qsizetype index) const;
  [[nodiscard]] qsizetype indexOf(Layer* layer) const;

  [[nodiscard]] qsizetype size() const;

  Layers::iterator begin();
  Layers::iterator end();

  Layers::const_iterator begin() const;
  Layers::const_iterator end() const;

  [[nodiscard]] std::unique_ptr<Layer> clone() const override;

  void serialize(utils::OArchive& archive) const override;
  void deserialize(utils::IArchive& archive) override;

 protected:
  void init(const GroupLayer* group_layer);

 private:
  Layers m_layers;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GROUP_LAYER_H