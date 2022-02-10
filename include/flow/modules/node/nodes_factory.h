#ifndef FLOW_NODES_FACTORY_H
#define FLOW_NODES_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QHash>
/* ---------------------------------- Standard ------------------------------ */
#include <unordered_map>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class Node;

  class NODE_API NodesFactory : public QObject
  {
    Q_OBJECT

  private:
    using Factory = std::function<std::unique_ptr<Node>()>;

  public:
    explicit NodesFactory(QObject* parent = nullptr);
    ~NodesFactory() override;

    [[nodiscard]] std::unique_ptr<Node> createNode(const QString& id) const;
    [[nodiscard]] QStringList getAvailableNodes() const;

  protected:
    void registerFactory(const QString& id, const Factory &factory);
    void unregisterFactory(const QString& id);

  private:
    QHash<QString, Factory> m_factories;
  };

} // namespace node

Q_DECLARE_INTERFACE(node::NodesFactory, "org.flow.NodesFactory")

#endif//FLOW_NODES_FACTORY_H
