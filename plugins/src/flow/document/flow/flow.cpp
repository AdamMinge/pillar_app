/* ----------------------------------- Local -------------------------------- */
#include "flow/document/flow/flow.h"

#include "flow/document/flow/group_layer.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/archive.h>
#include <qtils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow {

Flow::Flow() : m_root_layer(std::make_unique<GroupLayer>()) {}

Flow::~Flow() = default;

GroupLayer *Flow::getRootLayer() const { return m_root_layer.get(); }

void Flow::serialize(qtils::OArchive &archive) const {
  Object::serialize(archive);

  archive << qtils::ArchiveProperty("root_layer", m_root_layer);
}

void Flow::deserialize(qtils::IArchive &archive) {
  Object::deserialize(archive);

  archive >> qtils::ArchiveProperty("root_layer", m_root_layer);
}

}  // namespace flow
