#ifndef FLOW_NODE_OR_H
#define FLOW_NODE_OR_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/api/node/node.h>
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API NodeOr : public api::node::INode
  {
  public:
    explicit NodeOr();
    ~NodeOr() override;

    [[nodiscard]] unsigned
    getPinsCounts(api::node::IPin::PinType type) const override;

    [[nodiscard]] const api::node::IPin &getPin(api::node::IPin::PinType type,
                                                unsigned index) const override;
    [[nodiscard]] api::node::IPin &getPin(api::node::IPin::PinType type,
                                          unsigned index) override;
  };

}// namespace plugins::node::logic

#endif//FLOW_NODE_OR_H
