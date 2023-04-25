/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/add_remove_node.h"

#include "flow_document/flow/flow_node.h"
#include "flow_document/flow/flow_node_factory.h"
#include "flow_document/flow_document.h"
/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {
FlowNodeFactory *getFlowNodeFactory(const QString &node_to_create_id) {
  auto node_factories_list =
      egnite::PluginManager::getInstance().getObjects<FlowNodeFactories>();

  for (auto node_factories : node_factories_list)
    if (auto factory = node_factories->getFactory(node_to_create_id); factory)
      return factory;

  Q_ASSERT(false);
}
};  // namespace

/* ---------------------------- AddRemoveNodeCommand ------------------------ */

AddRemoveNodeCommand::AddRemoveNodeCommand(QString name, FlowDocument *document,
                                           FlowNode *node_to_remove,
                                           egnite::Command *parent)
    : egnite::Command(std::move(name), parent),
      m_document(document),
      m_node_to_remove(node_to_remove),
      m_node_to_add(nullptr) {}

AddRemoveNodeCommand::AddRemoveNodeCommand(QString name, FlowDocument *document,
                                           const QString &node_to_create_id,
                                           const QPointF &pos,
                                           egnite::Command *parent)
    : egnite::Command(std::move(name), parent),
      m_document(document),
      m_node_to_remove(nullptr) {
  m_node_to_add = getFlowNodeFactory(node_to_create_id)->create().release();
  m_node_to_add->setPosition(pos);
}

AddRemoveNodeCommand::~AddRemoveNodeCommand() { delete m_node_to_add; }

void AddRemoveNodeCommand::addNode() {
  Q_ASSERT(m_node_to_add);
  // m_document->addNode(m_node_to_add);
  std::swap(m_node_to_add, m_node_to_remove);
}

void AddRemoveNodeCommand::removeNode() {
  Q_ASSERT(m_node_to_remove);
  // m_document->removeNode(m_node_to_remove);
  std::swap(m_node_to_add, m_node_to_remove);
}

/* ------------------------------ AddNodeCommand ---------------------------- */

AddNodeCommand::AddNodeCommand(FlowDocument *document,
                               const QString &node_to_create_id,
                               const QPointF &position, Command *parent)
    : AddRemoveNodeCommand(QLatin1String("AddNode"), document,
                           node_to_create_id, position, parent) {
  setText(QObject::tr("Add Node"));
}

AddNodeCommand::~AddNodeCommand() = default;

void AddNodeCommand::redo() { addNode(); }

void AddNodeCommand::undo() { removeNode(); }

/* ----------------------------- RemoveNodeCommand -------------------------- */

RemoveNodeCommand::RemoveNodeCommand(FlowDocument *document,
                                     FlowNode *node_to_remove, Command *parent)
    : AddRemoveNodeCommand(QLatin1String("RemoveNode"), document,
                           node_to_remove, parent) {
  setText(QObject::tr("Remove Node"));
}

RemoveNodeCommand::~RemoveNodeCommand() = default;

void RemoveNodeCommand::redo() { removeNode(); }

void RemoveNodeCommand::undo() { addNode(); }

}  // namespace flow_document