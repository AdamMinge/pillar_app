/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/node_item_factory.h"

#include "flow_document/component/scene/item/node_item.h"
#include "flow_document/flow/node.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------- NodeItemFactory -------------------------- */

NodeItemFactory::NodeItemFactory(QObject* parent) : ItemFactory(parent) {}

NodeItemFactory::~NodeItemFactory() = default;

QString NodeItemFactory::getObjectClassName() const {
  return Node::sGetClassName();
}

ObjectItem* NodeItemFactory::create(Object* object, FlowDocument* document,
                                    QGraphicsItem* parent) const {
  return new NodeItem(static_cast<Node*>(object), document, parent);
}

}  // namespace flow_document