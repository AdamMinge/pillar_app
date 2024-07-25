/* ----------------------------------- Local -------------------------------- */
#include "flow/document/command/change_node.h"

#include "flow/document/document.h"
#include "flow/document/event/node_change_event.h"
#include "flow/document/flow/node.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/container/map.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------ SetNodesVisible --------------------------- */

SetNodesVisible::SetNodesVisible(FlowDocument* document, QList<Node*> nodes,
                                 bool visible, Command* parent)
    : ChangeValue<Node, bool>(QLatin1String("SetNodesVisible"), document,
                              std::move(nodes), visible, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action =
      visible ? QObject::tr("Visible") : QObject::tr("Invisible");

  setText(QString("%1 %2").arg(what, action));
}

SetNodesVisible::~SetNodesVisible() = default;

bool SetNodesVisible::getValue(const Node* node) const {
  return node->isVisible();
}

void SetNodesVisible::setValue(Node* node, const bool& visible) {
  node->setVisible(visible);
  getDocument()->event(
      NodesChangeEvent({node}, NodesChangeEvent::Property::Visible));
}

/* ------------------------------- SetNodesName ----------------------------- */

SetNodesName::SetNodesName(FlowDocument* document, QList<Node*> nodes,
                           QString name, Command* parent)
    : ChangeValue<Node, QString>(QLatin1String("SetNodesName"), document,
                                 std::move(nodes), name, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Name");
  setText(QString("%1 %2").arg(what, action));
}

SetNodesName::~SetNodesName() = default;

QString SetNodesName::getValue(const Node* node) const {
  return node->getName();
}

void SetNodesName::setValue(Node* node, const QString& name) {
  node->setName(name);
  getDocument()->event(
      NodesChangeEvent({node}, NodesChangeEvent::Property::Name));
}

/* ------------------------------ SetNodesPosition -------------------------- */

SetNodesPosition::SetNodesPosition(FlowDocument* document, QList<Node*> nodes,
                                   QPointF position, Command* parent)
    : ChangeValue<Node, QPointF>(QLatin1String("SetNodesPosition"), document,
                                 std::move(nodes), position, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Position");
  setText(QString("%1 %2").arg(what, action));
}

SetNodesPosition::~SetNodesPosition() = default;

QPointF SetNodesPosition::getValue(const Node* node) const {
  return node->getPosition();
}

void SetNodesPosition::setValue(Node* node, const QPointF& position) {
  node->setPosition(position);
  getDocument()->event(
      NodesChangeEvent({node}, NodesChangeEvent::Property::Position));
}

/* -------------------------- SetNodesCustomProperty ------------------------ */

SetNodesCustomProperty::SetNodesCustomProperty(FlowDocument* document,
                                               QList<Node*> nodes,
                                               QString property, QVariant value,
                                               Command* parent)
    : ChangeValue<Node, QVariant>(
          QString("SetNodesCustomProperty-%1").arg(property), document,
          std::move(nodes), std::move(value), parent),
      m_property(std::move(property)) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Custom Property");
  setText(QString("%1 %2").arg(what, action));
}

SetNodesCustomProperty::~SetNodesCustomProperty() = default;

QVariant SetNodesCustomProperty::getValue(const Node* node) const {
  return node->getProperty(m_property);
}

void SetNodesCustomProperty::setValue(Node* node, const QVariant& value) {
  node->setProperty(m_property, value);
  getDocument()->event(
      NodesChangeEvent({node}, NodesChangeEvent::Property::Custom));
}

/* ------------------------- AddRemoveNodesProperties ---------------------- */

AddRemoveNodesProperties::AddRemoveNodesProperties(QString name,
                                                   FlowDocument* document,
                                                   QList<Node*> nodes,
                                                   QVariantMap properties,
                                                   Command* parent)
    : pillar::Command(name, parent),
      m_document(document),
      m_nodes(std::move(nodes)),
      m_properties(std::move(properties)) {}

AddRemoveNodesProperties::~AddRemoveNodesProperties() = default;

void AddRemoveNodesProperties::addProperties() {
  for (auto node : m_nodes) {
    auto& old_properties = node->getProperties();
    auto new_properties = old_properties;
    new_properties.insert(m_properties);

    Q_ASSERT(new_properties.size() ==
             old_properties.size() + m_properties.size());

    node->setProperties(new_properties);

    m_document->event(
        NodesChangeEvent({node}, NodesChangeEvent::Property::Custom));
  }
}

void AddRemoveNodesProperties::removeProperties() {
  for (auto node : m_nodes) {
    auto& old_properties = node->getProperties();

    auto new_properties = old_properties;
    for (auto key : m_properties.keys()) {
      Q_ASSERT(old_properties.contains(key));
      m_properties[key] = old_properties[key];

      new_properties.remove(key);
    }

    node->setProperties(new_properties);

    m_document->event(
        NodesChangeEvent({node}, NodesChangeEvent::Property::Custom));
  }
}

/* ---------------------------- AddNodesProperties -------------------------- */

AddNodesProperties::AddNodesProperties(FlowDocument* document,
                                       QList<Node*> nodes,
                                       QVariantMap properties, Command* parent)
    : AddRemoveNodesProperties(QLatin1String("AddNodesProperties"), document,
                               std::move(nodes), std::move(properties)) {
  const auto what =
      QObject::tr("Add Custom Property(s)", nullptr, m_properties.size());
  setText(what);
}

AddNodesProperties::~AddNodesProperties() = default;

void AddNodesProperties::undo() { removeProperties(); }

void AddNodesProperties::redo() { addProperties(); }

/* --------------------------- RemoveNodesProperties ------------------------ */

RemoveNodesProperties::RemoveNodesProperties(FlowDocument* document,
                                             QList<Node*> nodes,
                                             QStringList properties,
                                             Command* parent)
    : AddRemoveNodesProperties(QLatin1String("RemoveNodesProperties"), document,
                               std::move(nodes),
                               qtils::mapFromKeys(properties, QVariant{})) {
  const auto what =
      QObject::tr("Remove Custom Property(s)", nullptr, m_properties.size());
  setText(what);
}

RemoveNodesProperties::~RemoveNodesProperties() = default;

void RemoveNodesProperties::undo() { addProperties(); }

void RemoveNodesProperties::redo() { removeProperties(); }

}  // namespace flow
