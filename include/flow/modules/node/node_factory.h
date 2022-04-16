#ifndef FLOW_NODE_FACTORY_H
#define FLOW_NODE_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIcon>
/* ---------------------------------- Standard ------------------------------ */
#include <functional>
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class Node;

  class NODE_API NodeFactory
  {
  public:
    using Creator = std::function<std::unique_ptr<Node>()>;

  public:
    explicit NodeFactory();
    explicit NodeFactory(Creator creator, QString name, QIcon icon);
    ~NodeFactory();

    [[nodiscard]] Creator getCreator() const;
    [[nodiscard]] QString getName() const;
    [[nodiscard]] QIcon getIcon() const;

    [[nodiscard]] std::unique_ptr<Node> operator()() const;

  private:
    Creator m_creator;
    QString m_name;
    QIcon m_icon;
  };

}// namespace node

#endif//FLOW_NODE_FACTORY_H
