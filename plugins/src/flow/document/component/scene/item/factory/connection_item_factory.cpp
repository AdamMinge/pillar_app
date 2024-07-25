/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/factory/connection_item_factory.h"

#include "flow/document/component/scene/item/connection_item.h"
#include "flow/document/flow/connection.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow {

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

}  // namespace flow