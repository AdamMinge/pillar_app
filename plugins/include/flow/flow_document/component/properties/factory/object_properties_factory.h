#ifndef FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H
#define FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ObjectProperties;

/* -------------------------- ObjectPropertiesFactory ----------------------- */

class FLOW_DOCUMENT_API ObjectPropertiesFactory : public QObject {
  Q_OBJECT

 public:
  explicit ObjectPropertiesFactory(QObject* parent = nullptr);
  ~ObjectPropertiesFactory() override;

  [[nodiscard]] virtual ObjectProperties* create(
      QObject* parent = nullptr) const = 0;

  [[nodiscard]] virtual QString getObjectClassName() const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ObjectPropertiesFactory,
                    "org.flow.ObjectPropertiesFactory")

#endif  // FLOW_DOCUMENT_OBJECT_PROPERTIES_FACTORY_H