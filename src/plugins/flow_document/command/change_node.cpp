/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_node.h"

#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ SetNodesVisible --------------------------- */

SetNodesVisible::SetNodesVisible(FlowDocument* document, QList<Node*> layers,
                                 bool visible, Command* parent)
    : ChangeValue<Node, bool>(QLatin1String("SetNodesVisible"), document,
                              std::move(layers), visible, parent) {
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

SetNodesName::SetNodesName(FlowDocument* document, QList<Node*> layers,
                           QString name, Command* parent)
    : ChangeValue<Node, QString>(QLatin1String("SetNodesName"), document,
                                 std::move(layers), name, parent) {
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

}  // namespace flow_document
