#ifndef FLOW_DOCUMENT_NODE_FACTORY_H
#define FLOW_DOCUMENT_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
#include "flow_document/flow/factory/factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;

/* -------------------------------- NodeFactory ----------------------------- */

class NodeFactory : public Factory {
  Q_OBJECT

 public:
  explicit NodeFactory(QString name);
  ~NodeFactory() override;

  [[nodiscard]] virtual QString getNodeType() const = 0;
  [[nodiscard]] virtual std::unique_ptr<Node> create() const = 0;
};

/* ------------------------------ BaseNodeFactory --------------------------- */

template <IsNode NODE>
class BaseNodeFactory : public NodeFactory {
 public:
  explicit BaseNodeFactory(QString name);

  [[nodiscard]] QString getNodeType() const override;
  [[nodiscard]] std::unique_ptr<Node> create() const override;
};

template <IsNode NODE>
BaseNodeFactory<NODE>::BaseNodeFactory(QString name)
    : NodeFactory(std::move(name)) {}

template <IsNode NODE>
QString BaseNodeFactory<NODE>::getNodeType() const {
  return NODE::getStaticClassName();
}

template <IsNode NODE>
std::unique_ptr<Node> BaseNodeFactory<NODE>::create() const {
  return std::make_unique<NODE>();
}

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_FACTORY_H