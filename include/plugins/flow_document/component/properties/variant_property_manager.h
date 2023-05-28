#ifndef FLOW_DOCUMENT_VARIANT_PROPERTY_MANAGER_H
#define FLOW_DOCUMENT_VARIANT_PROPERTY_MANAGER_H

/* ----------------------------------- Utils -------------------------------- */
#include <utils/property_browser/variant_property.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class VariantPropertyManager : public utils::QtVariantPropertyManager {
  Q_OBJECT
 public:
  VariantPropertyManager(QObject *parent = nullptr);
  ~VariantPropertyManager() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_VARIANT_PROPERTY_MANAGER_H
