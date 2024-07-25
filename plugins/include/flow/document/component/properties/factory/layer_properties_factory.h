#ifndef FLOW_DOCUMENT_LAYER_PROPERTIES_FACTORY_H
#define FLOW_DOCUMENT_LAYER_PROPERTIES_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------- LayerPropertiesFactory ----------------------- */

class LIB_FLOW_DOCUMENT_API LayerPropertiesFactory
    : public ObjectPropertiesFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ObjectPropertiesFactory)

 public:
  explicit LayerPropertiesFactory(QObject* parent = nullptr);

  [[nodiscard]] ObjectProperties* create(
      QObject* parent = nullptr) const override;

  [[nodiscard]] QString getObjectClassName() const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_LAYER_PROPERTIES_FACTORY_H