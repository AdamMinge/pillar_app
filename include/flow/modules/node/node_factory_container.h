#ifndef FLOW_NODE_FACTORY_CONTAINER_H
#define FLOW_NODE_FACTORY_CONTAINER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ---------------------------------- Standard ------------------------------ */
#include <memory>
#include <unordered_map>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class NodeFactory;

  class NODE_API NodeFactoryContainer : public QObject
  {
    Q_OBJECT

  public:
    explicit NodeFactoryContainer();
    ~NodeFactoryContainer() override;

    void addFactory(std::unique_ptr<NodeFactory> node_factory);
    void removeFactory(const NodeFactory &node_factory);

    [[nodiscard]] std::list<std::unique_ptr<NodeFactory>>::const_iterator
    begin() const;
    [[nodiscard]] std::list<std::unique_ptr<NodeFactory>>::const_iterator
    end() const;

    [[nodiscard]] std::list<std::unique_ptr<NodeFactory>>::iterator begin();
    [[nodiscard]] std::list<std::unique_ptr<NodeFactory>>::iterator end();

    [[nodiscard]] size_t size() const;

    [[nodiscard]] virtual QString getName() const = 0;
    [[nodiscard]] virtual QIcon getIcon() const = 0;

  private:
    std::list<std::unique_ptr<NodeFactory>> m_factories;
  };

}// namespace node

Q_DECLARE_INTERFACE(node::NodeFactoryContainer, "org.flow.NodeFactoryContainer")

#endif//FLOW_NODE_FACTORY_CONTAINER_H
