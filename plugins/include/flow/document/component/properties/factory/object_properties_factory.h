#ifndef FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H
#define FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class ObjectProperties;

/* -------------------------- ObjectPropertiesFactory ----------------------- */

class LIB_FLOW_DOCUMENT_API ObjectPropertiesFactory : public QObject {
  Q_OBJECT

 public:
  explicit ObjectPropertiesFactory(QObject* parent = nullptr);
  ~ObjectPropertiesFactory() override;

  [[nodiscard]] virtual ObjectProperties* create(
      QObject* parent = nullptr) const = 0;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::ObjectPropertiesFactory,
                    "org.flow.ObjectPropertiesFactory")

#endif  // FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H