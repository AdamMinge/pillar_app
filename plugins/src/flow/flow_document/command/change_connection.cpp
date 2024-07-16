/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_connection.h"

#include "flow_document/event/connection_change_event.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow_document.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/container/map.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- SetConnectionsVisible ------------------------ */

SetConnectionsVisible::SetConnectionsVisible(FlowDocument* document,
                                             QList<Connection*> connections,
                                             bool visible, Command* parent)
    : ChangeValue<Connection, bool>(QLatin1String("SetConnectionsVisible"),
                                    document, std::move(connections), visible,
                                    parent) {
  const auto what =
      QObject::tr("Set Connection(s)", nullptr, getObjects().size());
  const auto action =
      visible ? QObject::tr("Visible") : QObject::tr("Invisible");

  setText(QString("%1 %2").arg(what, action));
}

SetConnectionsVisible::~SetConnectionsVisible() = default;

bool SetConnectionsVisible::getValue(const Connection* connection) const {
  return connection->isVisible();
}

void SetConnectionsVisible::setValue(Connection* connection,
                                     const bool& visible) {
  connection->setVisible(visible);
  getDocument()->event(ConnectionsChangeEvent(
      {connection}, ConnectionsChangeEvent::Property::Visible));
}

/* ---------------------------- SetConnectionsName -------------------------- */

SetConnectionsName::SetConnectionsName(FlowDocument* document,
                                       QList<Connection*> connections,
                                       QString name, Command* parent)
    : ChangeValue<Connection, QString>(QLatin1String("SetConnectionsName"),
                                       document, std::move(connections), name,
                                       parent) {
  const auto what =
      QObject::tr("Set Connection(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Name");
  setText(QString("%1 %2").arg(what, action));
}

SetConnectionsName::~SetConnectionsName() = default;

QString SetConnectionsName::getValue(const Connection* connection) const {
  return connection->getName();
}

void SetConnectionsName::setValue(Connection* connection, const QString& name) {
  connection->setName(name);
  getDocument()->event(ConnectionsChangeEvent(
      {connection}, ConnectionsChangeEvent::Property::Name));
}

/* ----------------------- SetConnectionsCustomProperty --------------------- */

SetConnectionsCustomProperty::SetConnectionsCustomProperty(
    FlowDocument* document, QList<Connection*> connections, QString property,
    QVariant value, Command* parent)
    : ChangeValue<Connection, QVariant>(
          QString("SetConnectionsCustomProperty-%1").arg(property), document,
          std::move(connections), std::move(value), parent),
      m_property(std::move(property)) {
  const auto what =
      QObject::tr("Set Connection(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Custom Property");
  setText(QString("%1 %2").arg(what, action));
}

SetConnectionsCustomProperty::~SetConnectionsCustomProperty() = default;

QVariant SetConnectionsCustomProperty::getValue(
    const Connection* connection) const {
  return connection->getProperty(m_property);
}

void SetConnectionsCustomProperty::setValue(Connection* connection,
                                            const QVariant& value) {
  connection->setProperty(m_property, value);
  getDocument()->event(ConnectionsChangeEvent(
      {connection}, ConnectionsChangeEvent::Property::Custom));
}

/* ---------------------- AddRemoveConnectionsProperties -------------------- */

AddRemoveConnectionsProperties::AddRemoveConnectionsProperties(
    QString name, FlowDocument* document, QList<Connection*> connections,
    QVariantMap properties, Command* parent)
    : pillar::Command(name, parent),
      m_document(document),
      m_connections(std::move(connections)),
      m_properties(std::move(properties)) {}

AddRemoveConnectionsProperties::~AddRemoveConnectionsProperties() = default;

void AddRemoveConnectionsProperties::addProperties() {
  for (auto connection : m_connections) {
    auto& old_properties = connection->getProperties();
    auto new_properties = old_properties;
    new_properties.insert(m_properties);

    Q_ASSERT(new_properties.size() ==
             old_properties.size() + m_properties.size());

    connection->setProperties(new_properties);

    m_document->event(ConnectionsChangeEvent(
        {connection}, ConnectionsChangeEvent::Property::Custom));
  }
}

void AddRemoveConnectionsProperties::removeProperties() {
  for (auto connection : m_connections) {
    auto& old_properties = connection->getProperties();

    auto new_properties = old_properties;
    for (auto key : m_properties.keys()) {
      Q_ASSERT(old_properties.contains(key));
      m_properties[key] = old_properties[key];

      new_properties.remove(key);
    }

    connection->setProperties(new_properties);

    m_document->event(ConnectionsChangeEvent(
        {connection}, ConnectionsChangeEvent::Property::Custom));
  }
}

/* ------------------------- AddConnectionsProperties ----------------------- */

AddConnectionsProperties::AddConnectionsProperties(
    FlowDocument* document, QList<Connection*> connections,
    QVariantMap properties, Command* parent)
    : AddRemoveConnectionsProperties(QLatin1String("AddConnectionsProperties"),
                                     document, std::move(connections),
                                     std::move(properties)) {
  const auto what =
      QObject::tr("Add Custom Property(s)", nullptr, m_properties.size());
  setText(what);
}

AddConnectionsProperties::~AddConnectionsProperties() = default;

void AddConnectionsProperties::undo() { removeProperties(); }

void AddConnectionsProperties::redo() { addProperties(); }

/* ------------------------ RemoveConnectionsProperties --------------------- */

RemoveConnectionsProperties::RemoveConnectionsProperties(
    FlowDocument* document, QList<Connection*> connections,
    QStringList properties, Command* parent)
    : AddRemoveConnectionsProperties(
          QLatin1String("RemoveConnectionsProperties"), document,
          std::move(connections), qtils::mapFromKeys(properties, QVariant{})) {
  const auto what =
      QObject::tr("Remove Custom Property(s)", nullptr, m_properties.size());
  setText(what);
}

RemoveConnectionsProperties::~RemoveConnectionsProperties() = default;

void RemoveConnectionsProperties::undo() { addProperties(); }

void RemoveConnectionsProperties::redo() { removeProperties(); }

}  // namespace flow_document
