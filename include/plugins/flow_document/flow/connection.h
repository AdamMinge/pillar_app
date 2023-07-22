#ifndef FLOW_DOCUMENT_CONNECTION_H
#define FLOW_DOCUMENT_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Connection : public Object {
  FLOW_OBJECT_CLASS(Connection, Object)

 public:
  explicit Connection();
  ~Connection() override;

  void serialize(utils::OArchive &archive) const override;
  void deserialize(utils::IArchive &archive) override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_H