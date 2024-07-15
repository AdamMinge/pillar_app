/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/connection_properties.h"

#include "flow_document/command/change_connection.h"
#include "flow_document/component/properties/variant_property_manager.h"
#include "flow_document/event/connection_change_event.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- ConnectionProperties ------------------------- */

ConnectionProperties::ConnectionProperties(QObject* parent)
    : ObjectProperties(tr("Connection"), parent) {}

ConnectionProperties::~ConnectionProperties() = default;

void ConnectionProperties::init() {
  auto prop = getObjectProperties();
  prop->createProperty(Property::Name, QMetaType::QString, tr("Name"));
  prop->createProperty(Property::Visible, QMetaType::Bool, tr("Visible"));
}

Connection* ConnectionProperties::getConnection() const {
  return static_cast<Connection*>(getObject());
}

void ConnectionProperties::addProperty(const QString& name,
                                       const QVariant& value) {
  getDocument()->getUndoStack()->push(new AddConnectionsProperties(
      getDocument(), {getConnection()}, {std::make_pair(name, value)}));
}

void ConnectionProperties::removeProperty(const QString& name) {
  getDocument()->getUndoStack()->push(new RemoveConnectionsProperties(
      getDocument(), {getConnection()}, {name}));
}

void ConnectionProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == ConnectionsChangeEvent::type) {
    auto& e = static_cast<const ConnectionsChangeEvent&>(event);
    if (e.getConnections().contains(getConnection())) update();
  }
}

void ConnectionProperties::updateObject() {
  auto prop = getObjectProperties();
  if (auto connection = getConnection(); connection) {
    prop->getPropertyById(Property::Name)->setValue(connection->getName());
    prop->getPropertyById(Property::Visible)->setValue(connection->isVisible());
  }
}

void ConnectionProperties::applyCustom(const QString& name,
                                       const QVariant& value) {
  getDocument()->getUndoStack()->push(new SetConnectionsCustomProperty(
      getDocument(), {getConnection()}, name, value));
}

void ConnectionProperties::applyObject(size_t id, const QVariant& value) {
  auto connection = getConnection();

  switch (id) {
    case Property::Name: {
      auto name = value.toString();
      if (connection->getName() != name) {
        getDocument()->getUndoStack()->push(
            new SetConnectionsName(getDocument(), {connection}, name));
      }

      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(new SetConnectionsVisible(
          getDocument(), {connection}, value.toBool()));
      break;
    }
  }
}

}  // namespace flow_document