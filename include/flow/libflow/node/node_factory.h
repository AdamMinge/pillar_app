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
    explicit NodeFactory(QString name, QIcon icon);
    ~NodeFactory() override;

    [[nodiscard]] virtual std::unique_ptr<Node> create() const = 0;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

  private:
    QString m_name;
    QIcon m_icon;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, Node>
  class LIB_FLOW_API BaseNodeFactory : public NodeFactory
  {
  public:
    explicit BaseNodeFactory(QString name, QIcon icon);

    [[nodiscard]] std::unique_ptr<Node> create() const override;
  };

  template<typename TYPE>
  requires std::derived_from<TYPE, Node>
  BaseNodeFactory<TYPE>::BaseNodeFactory(QString name, QIcon icon)
      : NodeFactory(name, icon)
  {}

  template<typename TYPE>
  requires std::derived_from<TYPE, Node> std::unique_ptr<Node>
  BaseNodeFactory<TYPE>::create()
  const { return std::make_unique<TYPE>(); }

  class LIB_FLOW_API NodeFactories : public QObject
  {
    Q_OBJECT

  public:
    explicit NodeFactories(QString name, QIcon icon);
    ~NodeFactories() override;

    void registerFactory(QString node_id, std::unique_ptr<NodeFactory> factory);
    void unregisterFactory(const QString &node_id);

    [[nodiscard]] virtual std::unique_ptr<Node>
    create(const QString &node_id) const;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

  private:
    std::map<QString, std::unique_ptr<NodeFactory>> m_factories;
    QString m_name;
    QIcon m_icon;
  };

}// namespace flow::node

Q_DECLARE_INTERFACE(flow::node::NodeFactories, "org.flow.NodeFactories")

#endif//FLOW_NODE_FACTORY_H
