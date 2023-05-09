#ifndef FLOW_DOCUMENT_FLOW_H
#define FLOW_DOCUMENT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupLayer;

class FLOW_DOCUMENT_API Flow : public Object {
 public:
  explicit Flow();
  ~Flow() override;

  [[nodiscard]] GroupLayer* getRootLayer() const;

 private:
  std::unique_ptr<GroupLayer> m_root_layer;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_H