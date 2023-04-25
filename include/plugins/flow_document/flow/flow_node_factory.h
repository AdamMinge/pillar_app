#ifndef FLOW_DOCUMENT_FLOW_NODE_FACTORY_H
#define FLOW_DOCUMENT_FLOW_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowNode;

class FLOW_DOCUMENT_API FlowNodeFactory : public QObject {
  Q_OBJECT

 public:
  explicit FlowNodeFactory(QString name, QString node_type);
  ~FlowNodeFactory() override;

  [[nodiscard]] virtual std::unique_ptr<FlowNode> create() const = 0;

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getNodeType() const;

 private:
  QString m_name;
  QString m_node_type;
};

template <typename TYPE>
requires std::derived_from<TYPE, FlowNode>
class BaseFlowNodeFactory : public FlowNodeFactory {
 public:
  explicit BaseFlowNodeFactory(QString name, QString node_type);

  [[nodiscard]] std::unique_ptr<FlowNode> create() const override;
};

template <typename TYPE>
requires std::derived_from<TYPE, FlowNode>
BaseFlowNodeFactory<TYPE>::BaseFlowNodeFactory(QString name, QString node_type)
    : FlowNodeFactory(std::move(name), std::move(node_type)) {}

template <typename TYPE>
requires std::derived_from<TYPE, FlowNode> std::unique_ptr<FlowNode>
BaseFlowNodeFactory<TYPE>::create()
const { return std::make_unique<TYPE>(); }

class FLOW_DOCUMENT_API FlowNodeFactories : public QObject {
  Q_OBJECT

 public:
  explicit FlowNodeFactories(QString name);
  ~FlowNodeFactories() override;

  void registerFactory(std::unique_ptr<FlowNodeFactory> factory);
  void unregisterFactory(const QString &node_type);

  [[nodiscard]] QStringList getNodeTypes() const;
  [[nodiscard]] FlowNodeFactory *getFactory(const QString &node_type) const;

  [[nodiscard]] virtual std::unique_ptr<FlowNode> create(
      const QString &node_type) const;

  [[nodiscard]] QString getName() const;

 private:
  std::unordered_map<QString, std::unique_ptr<FlowNodeFactory>> m_factories;
  QString m_name;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::FlowNodeFactories,
                    "org.flow.FlowNodeFactories")

#endif  // FLOW_DOCUMENT_FLOW_NODE_FACTORY_H
