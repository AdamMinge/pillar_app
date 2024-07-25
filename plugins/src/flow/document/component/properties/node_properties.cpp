/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/node_properties.h"

#include "flow/document/command/change_node.h"
#include "flow/document/component/properties/variant_property_manager.h"
#include "flow/document/document.h"
#include "flow/document/event/node_change_event.h"
#include "flow/document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------ NodeProperties ---------------------------- */

NodeProperties::NodeProperties(QObject* parent)
    : ObjectProperties(tr("Node"), parent) {}

NodeProperties::~NodeProperties() = default;

void NodeProperties::init() {
  auto prop = getObjectProperties();
  prop->createProperty(Property::Name, QMetaType::QString, tr("Name"));
  prop->createProperty(Property::Visible, QMetaType::Bool, tr("Visible"));
  prop->createProperty(Property::Position, QMetaType::QPointF, tr("Position"));
}

Node* NodeProperties::getNode() const {
  return static_cast<Node*>(getObject());
}

void NodeProperties::addProperty(const QString& name, const QVariant& value) {
  getDocument()->getUndoStack()->push(new AddNodesProperties(
      getDocument(), {getNode()}, {std::make_pair(name, value)}));
}

void NodeProperties::removeProperty(const QString& name) {
  getDocument()->getUndoStack()->push(
      new RemoveNodesProperties(getDocument(), {getNode()}, {name}));
}

void NodeProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == NodesChangeEvent::type) {
    auto& e = static_cast<const NodesChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void NodeProperties::updateObject() {
  auto prop = getObjectProperties();
  if (auto node = getNode(); node) {
    prop->getPropertyById(Property::Name)->setValue(node->getName());
    prop->getPropertyById(Property::Visible)->setValue(node->isVisible());
    prop->getPropertyById(Property::Position)->setValue(node->getPosition());
  }
}

void NodeProperties::applyCustom(const QString& name, const QVariant& value) {
  getDocument()->getUndoStack()->push(
      new SetNodesCustomProperty(getDocument(), {getNode()}, name, value));
}

void NodeProperties::applyObject(size_t id, const QVariant& value) {
  auto node = getNode();

  switch (id) {
    case Property::Name: {
      auto name = value.toString();
      if (node->getName() != name) {
        getDocument()->getUndoStack()->push(
            new SetNodesName(getDocument(), {node}, name));
      }

      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(
          new SetNodesVisible(getDocument(), {node}, value.toBool()));
      break;
    }

    case Property::Position: {
      getDocument()->getUndoStack()->push(
          new SetNodesPosition(getDocument(), {node}, value.toPointF()));
      break;
    }
  }
}

}  // namespace flow