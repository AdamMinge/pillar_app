/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/connection_item.h"

#include "flow_document/flow/connection.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ConnectionItem::ConnectionItem(Connection* connection, FlowDocument* document,
                               QGraphicsItem* parent)
    : ObjectItem(connection, document, parent) {}

ConnectionItem::~ConnectionItem() = default;

Connection* ConnectionItem::getConnection() const {
  return static_cast<Connection*>(getObject());
}

}  // namespace flow_document