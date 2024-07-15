/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/connection_item_factory.h"

#include "flow_document/component/scene/item/connection_item.h"
#include "flow_document/flow/connection.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- ConnectionItemFactory ----------------------- */

ConnectionItemFactory::ConnectionItemFactory(QObject* parent)
    : ItemFactory(parent) {}

ConnectionItemFactory::~ConnectionItemFactory() = default;

QString ConnectionItemFactory::getObjectClassName() const {
  return Connection::sGetClassName();
}

ObjectItem* ConnectionItemFactory::create(Object* object,
                                          FlowDocument* document,
                                          QGraphicsItem* parent) const {
  return new ConnectionItem(static_cast<Connection*>(object), document, parent);
}

}  // namespace flow_document