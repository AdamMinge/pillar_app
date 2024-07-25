#ifndef FLOW_DOCUMENT_FLOW_H
#define FLOW_DOCUMENT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
#include "flow/document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class GroupLayer;

class LIB_FLOW_DOCUMENT_API Flow : public Object {
  FLOW_OBJECT_CLASS(Flow, Object)

 public:
  explicit Flow();
  ~Flow() override;

  [[nodiscard]] GroupLayer *getRootLayer() const;

  void serialize(qtils::OArchive &archive) const override;
  void deserialize(qtils::IArchive &archive) override;

 private:
  std::unique_ptr<GroupLayer> m_root_layer;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_H