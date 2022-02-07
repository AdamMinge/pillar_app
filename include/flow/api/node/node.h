#ifndef FLOW_INTERFACE_NODE_H
#define FLOW_INTERFACE_NODE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
#include "flow/api/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace api::node
{

  class API_API INode : public QObject
  {
    Q_OBJECT

  public:
    explicit INode() = default;
    ~INode() override = default;

    [[nodiscard]] virtual unsigned getPinsCounts(IPin::PinType type) const = 0;

    [[nodiscard]] virtual const IPin &getPin(IPin::PinType type,
                                             unsigned index) const = 0;
    [[nodiscard]] virtual IPin &getPin(IPin::PinType type, unsigned index) = 0;

  private:
    std::vector<std::unique_ptr<IPin>> m_out_pins;
    std::vector<std::unique_ptr<IPin>> m_in_pins;
  };

}// namespace api::node

#endif//FLOW_INTERFACE_NODE_H
