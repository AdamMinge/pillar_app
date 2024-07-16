#ifndef FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H
#define FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Object;

/* ----------------------------------- Qtils -------------------------------- */

[[nodiscard]] ObjectProperties* createObjectProperties(
    Object* object, QObject* parent = nullptr);

[[nodiscard]] ObjectPropertiesFactory* getObjectPropertiesFactoryObject(
    Object* object);

}  // namespace flow_document

/* ----------------------- Helper macro to create factory ------------------- */

#define DECLARE_OBJECT_PROPERTIES_FACTORY(EXPORT_API, PROPERTIES, OBJECT) \
  class EXPORT_API PROPERTIES##Factory                                    \
      : public flow_document::ObjectPropertiesFactory {                   \
    Q_OBJECT                                                              \
    Q_INTERFACES(flow_document::ObjectPropertiesFactory)                  \
                                                                          \
   public:                                                                \
    explicit PROPERTIES##Factory(QObject* parent = nullptr)               \
        : flow_document::ObjectPropertiesFactory(parent) {}               \
                                                                          \
    [[nodiscard]] flow_document::ObjectProperties* create(                \
        QObject* parent = nullptr) const override {                       \
      return new PROPERTIES(parent);                                      \
    }                                                                     \
    [[nodiscard]] QString getObjectClassName() const override {           \
      return OBJECT::sGetClassName();                                     \
    }                                                                     \
  };

#endif  // FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H