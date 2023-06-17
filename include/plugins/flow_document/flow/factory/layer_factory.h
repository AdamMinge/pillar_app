#ifndef FLOW_DOCUMENT_LAYER_FACTORY_H
#define FLOW_DOCUMENT_LAYER_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
#include "flow_document/flow/factory/factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Layer;

/* -------------------------------- LayerFactory ---------------------------- */

class LayerFactory : public Factory {
  Q_OBJECT

 public:
  explicit LayerFactory(QString name);
  ~LayerFactory() override;

  [[nodiscard]] virtual QString getLayerType() const = 0;
  [[nodiscard]] virtual std::unique_ptr<Layer> create() const = 0;
};

/* ------------------------------ BaseLayerFactory -------------------------- */

template <IsLayer LAYER>
class BaseLayerFactory : public LayerFactory {
 public:
  explicit BaseLayerFactory(QString name);

  [[nodiscard]] QString getNodeType() const override;
  [[nodiscard]] std::unique_ptr<Layer> create() const override;
};

template <IsLayer LAYER>
BaseLayerFactory<LAYER>::BaseLayerFactory(QString name)
    : LayerFactory(std::move(name)) {}

template <IsLayer LAYER>
QString BaseLayerFactory<LAYER>::getNodeType() const {
  return LAYER::getStaticClassName();
}

template <IsLayer LAYER>
std::unique_ptr<Layer> BaseLayerFactory<LAYER>::create() const {
  return std::make_unique<LAYER>();
}

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_FACTORY_H