#ifndef FLOW_DOCUMENT_FLOW_H
#define FLOW_DOCUMENT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupLayer;

class FLOW_DOCUMENT_API Flow : public Object {
  FLOW_OBJECT_CLASS(Flow, Object)

 public:
  explicit Flow();
  ~Flow() override;

  [[nodiscard]] GroupLayer *getRootLayer() const;

  void serialize(utils::OArchive &archive) const override;
  void deserialize(utils::IArchive &archive) override;

 private:
  std::unique_ptr<GroupLayer> m_root_layer;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_H