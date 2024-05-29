/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/flow_item.h"

#include "flow_document/component/scene/item/factory/utils.h"
#include "flow_document/component/scene/item/layer_item.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowItem::FlowItem(Flow* flow, FlowDocument* document, QGraphicsItem* parent)
    : ObjectItem(flow, document, parent),
      m_root_item(createItem<LayerItem>(flow->getRootLayer(), document, this)) {
}

FlowItem::~FlowItem() = default;

Flow* FlowItem::getFlow() const { return static_cast<Flow*>(getObject()); }

}  // namespace flow_document