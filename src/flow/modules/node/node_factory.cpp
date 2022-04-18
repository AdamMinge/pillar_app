/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/node_factory.h"
#include "flow/modules/node/node.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  NodeFactory::NodeFactory() : NodeFactory({}, {}, {}, {}) {}

  NodeFactory::NodeFactory(
    QString id, Creator creator, QString name, QIcon icon)
      : m_id(std::move(id)), m_creator(std::move(creator)),
        m_icon(std::move(icon)), m_name(std::move(name))
  {}

  NodeFactory::~NodeFactory() = default;

  QString NodeFactory::getId() const { return m_id; }

  NodeFactory::Creator NodeFactory::getCreator() const { return m_creator; }

  QString NodeFactory::getName() const { return m_name; }

  QIcon NodeFactory::getIcon() const { return m_icon; }

  std::unique_ptr<Node> NodeFactory::operator()() const { return m_creator(); }

}// namespace node
