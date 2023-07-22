/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Connection::Connection() = default;

Connection::~Connection() = default;

void Connection::serialize(utils::OArchive &archive) const {
  Object::serialize(archive);
}

void Connection::deserialize(utils::IArchive &archive) {
  Object::deserialize(archive);
}

}  // namespace flow_document
