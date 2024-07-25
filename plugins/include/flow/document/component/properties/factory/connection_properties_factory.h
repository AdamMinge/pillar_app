#ifndef FLOW_DOCUMENT_CONNECTION_PROPERTIES_FACTORY_H
#define FLOW_DOCUMENT_CONNECTION_PROPERTIES_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------ ConnectionPropertiesFactory --------------------- */

class LIB_FLOW_DOCUMENT_API ConnectionPropertiesFactory
    : public ObjectPropertiesFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ObjectPropertiesFactory)

 public:
  explicit ConnectionPropertiesFactory(QObject* parent = nullptr);

  [[nodiscard]] ObjectProperties* create(
      QObject* parent = nullptr) const override;

  [[nodiscard]] QString getObjectClassName() const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_CONNECTION_PROPERTIES_FACTORY_H