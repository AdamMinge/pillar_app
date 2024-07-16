/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/flow_item_factory.h"

#include "flow_document/component/scene/item/flow_item.h"
#include "flow_document/flow/flow.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- FlowItemFactory -------------------------- */

FlowItemFactory::FlowItemFactory(QObject* parent) : ItemFactory(parent) {}

FlowItemFactory::~FlowItemFactory() = default;

QString FlowItemFactory::getObjectClassName() const {
  return Flow::sGetClassName();
}

ObjectItem* FlowItemFactory::create(Object* object, FlowDocument* document,
                                    QGraphicsItem* parent) const {
  return new FlowItem(static_cast<Flow*>(object), document, parent);
}

}  // namespace flow_document