/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/node_factory.h"

#include "flow_document/command/add_remove_node.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/pointer_cast/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Utils -------------------------------- */

namespace {

[[nodiscard]] QSet<QString> getAllNodeNames(FlowDocument* document,
                                            const QString& prefix) {
  auto names = QSet<QString>{};
  const auto nodes = getAllNodes(document);
  for (const auto node : nodes) {
    if (node->getName().startsWith(prefix)) names.insert(node->getName());
  }

  return names;
}

[[nodiscard]] QString getNewDefaultName(FlowDocument* document,
                                        const NodeFactory* factory) {
  auto name_template = factory->getName() + " %1";
  auto names = getAllNodeNames(document, factory->getName());

  auto index = 1;
  auto name = QString{};
  do {
    name = name_template.arg(index);
    ++index;
  } while (names.contains(name));

  return name;
}

}  // namespace

/* -------------------------------- NodeFactory ----------------------------- */

NodeFactory::NodeFactory(QString name, QString section, QObject* parent)
    : NodeFactory(std::move(name), std::move(section), QIcon(icons::x32::Node),
                  parent) {}

NodeFactory::NodeFactory(QString name, QString section, QIcon icon,
                         QObject* parent)
    : ObjectFactory(type, std::move(name), std::move(section), std::move(icon),
                    parent) {}

NodeFactory::~NodeFactory() = default;

bool NodeFactory::addObject(FlowDocument* document, InitMethod init) const {
  if (!canAddObject(document)) return false;

  auto node = utils::cast_unique_ptr<Node>(createObject());
  node->setName(getNewDefaultName(document, this));
  init(node.get());

  auto node_layer = static_cast<NodeLayer*>(document->getCurrentLayer());
  auto index = node_layer->nodesCount();

  const auto& selected_nodes = document->getSelectedNodes();
  if (selected_nodes.size() > 0) {
    auto selected_node = selected_nodes.at(0);
    index = node_layer->indexOfNode(selected_node) + 1;
  }

  auto entires = std::list<NodeEntry>{};
  entires.emplace_back(NodeEntry{node_layer, std::move(node), index});
  document->getUndoStack()->push(new AddNodes(document, std::move(entires)));

  return true;
}

bool NodeFactory::canAddObject(FlowDocument* document) const {
  auto current_layer = document->getCurrentLayer();
  if (current_layer && current_layer->isClassOrChild<NodeLayer>()) return true;

  return false;
}

}  // namespace flow_document