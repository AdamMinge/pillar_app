/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/flow_item.h"

#include "flow/document/component/scene/item/factory/utils.h"
#include "flow/document/component/scene/item/layer_item.h"
#include "flow/document/event/change_event.h"
#include "flow/document/flow/flow.h"
#include "flow/document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow {

FlowItem::FlowItem(Flow* flow, FlowDocument* document, QGraphicsItem* parent)
    : ObjectItem(flow, document, parent),
      m_root_item(createItem<LayerItem>(flow->getRootLayer(), document, this)) {
}

FlowItem::~FlowItem() = default;

Flow* FlowItem::getFlow() const { return static_cast<Flow*>(getObject()); }

}  // namespace flow