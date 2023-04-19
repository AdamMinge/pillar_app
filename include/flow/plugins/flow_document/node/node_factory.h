#ifndef FLOW_NODE_FACTORY_H
#define FLOW_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class Node;

class FLOW_DOCUMENT_API NodeFactory : public QObject {
  Q_OBJECT

 public:
  explicit NodeFactory(QString name, QString node_id);
  ~NodeFactory() override;

  [[nodiscard]] virtual std::unique_ptr<Node> create() const = 0;

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getNodeId() const;

 private:
  QString m_name;
  QString m_node_id;
};

template <typename TYPE>
requires std::derived_from<TYPE, Node>
class BaseNodeFactory : public NodeFactory {
 public:
  explicit BaseNodeFactory(QString name, QString node_id);

  [[nodiscard]] std::unique_ptr<Node> create() const override;
};

template <typename TYPE>
requires std::derived_from<TYPE, Node> BaseNodeFactory<TYPE>::BaseNodeFactory(
    QString name, QString node_id)
    : NodeFactory(std::move(name), std::move(node_id)) {}

template <typename TYPE>
requires std::derived_from<TYPE, Node> std::unique_ptr<Node>
BaseNodeFactory<TYPE>::create()
const { return std::make_unique<TYPE>(); }

class FLOW_DOCUMENT_API NodeFactories : public QObject {
  Q_OBJECT

 public:
  explicit NodeFactories(QString name);
  ~NodeFactories() override;

  void registerFactory(std::unique_ptr<NodeFactory> factory);
  void unregisterFactory(const QString &node_id);

  [[nodiscard]] QStringList getNodeIds() const;
  [[nodiscard]] NodeFactory *getFactory(const QString &node_id) const;

  [[nodiscard]] virtual std::unique_ptr<Node> create(
      const QString &node_id) const;

  [[nodiscard]] QString getName() const;

 private:
  std::map<QString, std::unique_ptr<NodeFactory>> m_factories;
  QString m_name;
};

}  // namespace plugin::flow_document

#endif  // FLOW_NODE_FACTORY_H
