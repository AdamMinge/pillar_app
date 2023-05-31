/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_node.h"

#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

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

}  // namespace flow_document
