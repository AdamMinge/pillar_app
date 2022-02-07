#ifndef FLOW_INTERFACE_PIN_H
#define FLOW_INTERFACE_PIN_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
/* -------------------------------------------------------------------------- */

namespace api::node
{

  class INodeData;

  class API_API IPin : public QObject
  {
    Q_OBJECT

  public:
    enum class ConnectionPolicy;
    enum class PinType;

  public:
    explicit IPin() = default;
    ~IPin() override = default;

  public Q_SLOTS:
    virtual void setCaption(const QString &caption) = 0;
    virtual void setData(std::shared_ptr<INodeData> data) = 0;
    virtual void
    setConnectionPolicy(api::node::IPin::ConnectionPolicy policy) = 0;

  Q_SIGNALS:
    void captionChanged(const QString &caption);
    void dataChanged(const api::node::INodeData &data);
    void connectionPolicyChanged(api::node::IPin::ConnectionPolicy policy);
  };

  enum class IPin::ConnectionPolicy
  {
    One,
    Many
  };

  enum class IPin::PinType
  {
    In,
    Out
  };

}// namespace api::node

#endif//FLOW_INTERFACE_PIN_H
