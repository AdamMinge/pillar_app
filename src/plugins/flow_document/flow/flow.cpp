/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow.h"

#include "flow_document/flow/group_layer.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

Flow::Flow()
    : Object(Type::Flow), m_root_layer(std::make_unique<GroupLayer>()) {}

Flow::~Flow() = default;

GroupLayer *Flow::getRootLayer() const { return m_root_layer.get(); }

void Flow::serialize(utils::OArchive &archive) const {
  Object::serialize(archive);

  archive << utils::ArchiveProperty("root_layer", *m_root_layer);
}

void Flow::deserialize(utils::IArchive &archive) {
  Object::deserialize(archive);
}

}  // namespace flow_document
