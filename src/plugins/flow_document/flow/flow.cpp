/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow.h"

#include "flow_document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Flow::Flow()
    : Object(Type::Flow), m_root_layer(std::make_unique<GroupLayer>()) {}

Flow::~Flow() = default;

GroupLayer* Flow::getRootLayer() const { return m_root_layer.get(); }

}  // namespace flow_document
