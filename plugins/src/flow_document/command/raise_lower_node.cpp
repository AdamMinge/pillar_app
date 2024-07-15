/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/raise_lower_node.h"

#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- RaiseLowerNodes ---------------------------- */

RaiseLowerNodes::RaiseLowerNodes(const QString& name, FlowDocument* document,
                                 QList<Node*> nodes, Command* parent)
    : egnite::Command(name, parent),
      m_document(document),
      m_nodes(std::move(nodes)) {
  std::sort(m_nodes.begin(), m_nodes.end(),
            [](const auto& left, const auto& right) {
              return getLayerHierarchicalId(left->getParent()) <
                     getLayerHierarchicalId(right->getParent());
            });
}

RaiseLowerNodes::~RaiseLowerNodes() = default;

void RaiseLowerNodes::raiseNodes() { moveNodes(true); }

void RaiseLowerNodes::lowerNodes() { moveNodes(false); }

void RaiseLowerNodes::moveNodes(bool raise) {
  auto current_node = m_document->getCurrentNode();
  auto selected_nodes = m_document->getSelectedNodes();

  auto process_layer = [this, raise](Node* node) {
    const auto step = raise ? 1 : -1;
    const auto parent = node->getParent();
    const auto index = parent->indexOfNode(node);
    const auto can_move = raise ? index < parent->nodesCount() - 1 : index > 0;

    this->moveNode(node, parent, index + step);
  };

  if (raise) {
    std::for_each(m_nodes.begin(), m_nodes.end(), process_layer);
  } else {
    std::for_each(m_nodes.rbegin(), m_nodes.rend(), process_layer);
  }

  m_document->setCurrentNode(current_node);
  m_document->setSelectedNodes(selected_nodes);
}

void RaiseLowerNodes::moveNode(Node* node, NodeLayer* parent, qsizetype index) {
  auto from_parent = node->getParent();
  auto from_index = from_parent->indexOfNode(node);

  Q_EMIT m_document->event(
      NodeEvent(NodeEvent::Event::AboutToBeRemoved, from_parent, from_index));
  auto reparent_layer = from_parent->takeNode(from_index);
  Q_ASSERT(reparent_layer);
  Q_EMIT m_document->event(
      NodeEvent(NodeEvent::Event::Removed, from_parent, from_index));

  Q_EMIT m_document->event(
      NodeEvent(NodeEvent::Event::AboutToBeAdded, parent, index));
  parent->insertNode(index, std::move(reparent_layer));
  Q_EMIT m_document->event(NodeEvent(NodeEvent::Event::Added, parent, index));
}

/* -------------------------------- RaiseNodes ------------------------------ */

RaiseNodes::RaiseNodes(FlowDocument* document, QList<Node*> nodes,
                       Command* parent)
    : RaiseLowerNodes(QLatin1String("RaiseNodes"), document, std::move(nodes),
                      parent) {
  const auto command_text =
      QObject::tr("Raise Node(s)", nullptr, m_nodes.size());
  setText(command_text);
}

RaiseNodes::~RaiseNodes() = default;

void RaiseNodes::undo() { lowerNodes(); }

void RaiseNodes::redo() { raiseNodes(); }

/* -------------------------------- LowerNodes ------------------------------ */

LowerNodes::LowerNodes(FlowDocument* document, QList<Node*> nodes,
                       Command* parent)
    : RaiseLowerNodes(QLatin1String("LowerNodes"), document, std::move(nodes),
                      parent) {
  const auto command_text =
      QObject::tr("Lower Node(s)", nullptr, m_nodes.size());
  setText(command_text);
}

LowerNodes::~LowerNodes() = default;

void LowerNodes::undo() { raiseNodes(); }

void LowerNodes::redo() { lowerNodes(); }

}  // namespace flow_document
