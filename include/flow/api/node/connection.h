#ifndef FLOW_INTERFACE_CONNECTION_H
#define FLOW_INTERFACE_CONNECTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
#include "flow/api/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace api::node
{

  class ITypeConverter;

  class API_API IConnection : public QObject
  {
    Q_OBJECT

  public:
    explicit IConnection() = default;
    ~IConnection() override = default;

    [[nodiscard]] virtual const IPin &getPin(IPin::PinType type) const = 0;
    [[nodiscard]] virtual IPin &getPin(IPin::PinType type) = 0;

  public Q_SLOTS:
    virtual void setConverter(std::shared_ptr<ITypeConverter> converter) = 0;

  Q_SIGNALS:
    void converterChanged(const api::node::ITypeConverter &converter);
  };

}// namespace api::node

#endif//FLOW_INTERFACE_CONNECTION_H
