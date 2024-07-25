#ifndef FLOW_DOCUMENT_VARIANT_PROPERTY_MANAGER_H
#define FLOW_DOCUMENT_VARIANT_PROPERTY_MANAGER_H

/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/property_browser/variant_property.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class VariantPropertyManager : public qtils::QtVariantPropertyManager {
  Q_OBJECT
 public:
  VariantPropertyManager(QObject *parent = nullptr);
  ~VariantPropertyManager() override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_VARIANT_PROPERTY_MANAGER_H
