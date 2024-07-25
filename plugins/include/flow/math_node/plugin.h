#ifndef MATH_NODE_PLUGIN_H
#define MATH_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/properties/factory/utils.h>
#include <flow/document/component/scene/item/factory/utils.h>
#include <flow/document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/component/properties/node_value_properties.h"
#include "flow/math_node/component/scene/item/node_value_item.h"
#include "flow/math_node/export.h"
#include "flow/math_node/flow/addition.h"
#include "flow/math_node/flow/division.h"
#include "flow/math_node/flow/equal.h"
#include "flow/math_node/flow/greater.h"
#include "flow/math_node/flow/greater_equal.h"
#include "flow/math_node/flow/lower.h"
#include "flow/math_node/flow/lower_equal.h"
#include "flow/math_node/flow/multiplication.h"
#include "flow/math_node/flow/negation.h"
#include "flow/math_node/flow/not_equal.h"
#include "flow/math_node/flow/power.h"
#include "flow/math_node/flow/square_root.h"
#include "flow/math_node/flow/subtraction.h"
#include "flow/math_node/flow/value.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_MATH_NODE_API MathNodePlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit MathNodePlugin();
  ~MathNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeAddition)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeDivision)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeMultiplication)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeNegation)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeSubtraction)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodePower)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeSquareRoot)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeEqual)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeGreaterEqual)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeGreater)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeLowerEqual)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeLower)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeNotEqual)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeDoubleEmitter)
DECLARE_NODE_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeDoubleReceiver)

DECLARE_GRAPHICS_ITEM_FACTORY(LIB_FLOW_MATH_NODE_API, MathNodeDoubleEmitterItem,
                              MathNodeDoubleEmitter);
DECLARE_GRAPHICS_ITEM_FACTORY(LIB_FLOW_MATH_NODE_API,
                              MathNodeDoubleReceiverItem,
                              MathNodeDoubleReceiver);

DECLARE_OBJECT_PROPERTIES_FACTORY(LIB_FLOW_MATH_NODE_API,
                                  MathNodeDoubleEmitterProperties,
                                  MathNodeDoubleEmitter);

}  // namespace flow

#endif  // MATH_NODE_PLUGIN_H
