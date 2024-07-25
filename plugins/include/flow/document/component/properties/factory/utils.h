#ifndef FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H
#define FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Object;

/* ----------------------------------- Qtils -------------------------------- */

[[nodiscard]] ObjectProperties* createObjectProperties(
    Object* object, QObject* parent = nullptr);

[[nodiscard]] ObjectPropertiesFactory* getObjectPropertiesFactoryObject(
    Object* object);

}  // namespace flow

/* ----------------------- Helper macro to create factory ------------------- */

#define DECLARE_OBJECT_PROPERTIES_FACTORY(EXPORT_API, PROPERTIES, OBJECT) \
  class EXPORT_API PROPERTIES##Factory                                    \
      : public flow::ObjectPropertiesFactory {                            \
    Q_OBJECT                                                              \
    Q_INTERFACES(flow::ObjectPropertiesFactory)                           \
                                                                          \
   public:                                                                \
    explicit PROPERTIES##Factory(QObject* parent = nullptr)               \
        : flow::ObjectPropertiesFactory(parent) {}                        \
                                                                          \
    [[nodiscard]] flow::ObjectProperties* create(                         \
        QObject* parent = nullptr) const override {                       \
      return new PROPERTIES(parent);                                      \
    }                                                                     \
    [[nodiscard]] QString getObjectClassName() const override {           \
      return OBJECT::sGetClassName();                                     \
    }                                                                     \
  };

#endif  // FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H