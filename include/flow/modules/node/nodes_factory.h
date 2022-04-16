#ifndef FLOW_NODES_FACTORY_H
#define FLOW_NODES_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QIcon>
#include <QObject>
/* ---------------------------------- Standard ------------------------------ */
#include <functional>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class Node;

  class NODE_API NodesFactory
  {
  public:
    class Factory;

  public:
    explicit NodesFactory();
    virtual ~NodesFactory();

    [[nodiscard]] std::unique_ptr<Node> createNode(const QString &id) const;
    [[nodiscard]] QStringList getAvailableNodes() const;

    void registerFactory(const QString &id, const Factory &factory);
    void unregisterFactory(const QString &id);

  private:
    QHash<QString, Factory> m_factories;
  };

  class NODE_API NodesFactory::Factory
  {
  public:
    using Creator = std::function<std::unique_ptr<Node>()>;

  public:
    explicit Factory();
    explicit Factory(Creator creator, QString name, QIcon icon);
    ~Factory();

    [[nodiscard]] const Creator &getCreator() const;
    [[nodiscard]] const QString &getName() const;
    [[nodiscard]] const QIcon &getIcon() const;

    [[nodiscard]] std::unique_ptr<Node> operator()() const;

  private:
    Creator m_creator;
    QString m_name;
    QIcon m_icon;
  };

}// namespace node

Q_DECLARE_INTERFACE(node::NodesFactory, "org.flow.NodesFactory")

#endif//FLOW_NODES_FACTORY_H
