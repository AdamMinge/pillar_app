#ifndef FLOW_NODE_FACTORY_H
#define FLOW_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class Node;

  class LIB_FLOW_API NodeFactory : public QObject
  {
    Q_OBJECT

  public:
    explicit NodeFactory(QString name);
    ~NodeFactory() override;

    [[nodiscard]] virtual std::unique_ptr<Node> create() const = 0;

    [[nodiscard]] QString getName() const;

  private:
    QString m_name;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, Node>
  class LIB_FLOW_API BaseNodeFactory : public NodeFactory
  {
  public:
    explicit BaseNodeFactory(QString name);

    [[nodiscard]] std::unique_ptr<Node> create() const override;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, Node>
  BaseNodeFactory<TYPE>::BaseNodeFactory(QString name)
      : NodeFactory(name)
  {}

  template<typename TYPE>
  requires std::derived_from<TYPE, Node> std::unique_ptr<Node>
  BaseNodeFactory<TYPE>::create()
  const { return std::make_unique<TYPE>(); }

  class LIB_FLOW_API NodeFactories : public QObject
  {
    Q_OBJECT

  public:
    explicit NodeFactories(QString name);
    ~NodeFactories() override;

    void registerFactory(QString node_id, std::unique_ptr<NodeFactory> factory);
    void unregisterFactory(const QString &node_id);

    [[nodiscard]] QStringList getNodeIds() const;
    [[nodiscard]] NodeFactory *getFactory(const QString &node_id) const;

    [[nodiscard]] virtual std::unique_ptr<Node>
    create(const QString &node_id) const;

    [[nodiscard]] QString getName() const;

  private:
    std::map<QString, std::unique_ptr<NodeFactory>> m_factories;
    QString m_name;
  };

}// namespace flow::node

Q_DECLARE_INTERFACE(flow::node::NodeFactories, "org.flow.NodeFactories")

#endif//FLOW_NODE_FACTORY_H
