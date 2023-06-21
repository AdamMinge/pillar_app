/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/flow_graphics_item.h"

#include "flow_document/component/scene/item/factory/graphics_item_factory.h"
#include "flow_document/component/scene/item/layer_graphics_item.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowGraphicsItem::FlowGraphicsItem(Flow* flow, FlowDocument* document,
                                   QGraphicsItem* parent)
    : GraphicsItem(flow, document, parent),
      m_root_layer_item(createGraphicsItem<LayerGraphicsItem>(
          flow->getRootLayer(), document, this)) {}

FlowGraphicsItem::~FlowGraphicsItem() = default;

Flow* FlowGraphicsItem::getFlow() const {
  return static_cast<Flow*>(getObject());
}

}  // namespace flow_document