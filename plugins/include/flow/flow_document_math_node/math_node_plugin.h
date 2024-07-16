#ifndef MATH_NODE_PLUGIN_H
#define MATH_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/factory/utils.h>
#include <flow_document/component/scene/item/factory/utils.h>
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "component/properties/math_node_value_properties.h"
#include "component/scene/item/math_node_value_item.h"
#include "export.h"
#include "flow/math_node_addition.h"
#include "flow/math_node_division.h"
#include "flow/math_node_equal.h"
#include "flow/math_node_greater.h"
#include "flow/math_node_greater_equal.h"
#include "flow/math_node_lower.h"
#include "flow/math_node_lower_equal.h"
#include "flow/math_node_multiplication.h"
#include "flow/math_node_negation.h"
#include "flow/math_node_not_equal.h"
#include "flow/math_node_power.h"
#include "flow/math_node_square_root.h"
#include "flow/math_node_subtraction.h"
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodePlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit MathNodePlugin();
  ~MathNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeAddition)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeDivision)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeMultiplication)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeNegation)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeSubtraction)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodePower)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeSquareRoot)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeEqual)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeGreaterEqual)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeGreater)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeLowerEqual)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeLower)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeNotEqual)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeDoubleEmitter)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeDoubleReceiver)

DECLARE_GRAPHICS_ITEM_FACTORY(MATH_NODE_API, MathNodeDoubleEmitterItem,
                              MathNodeDoubleEmitter);
DECLARE_GRAPHICS_ITEM_FACTORY(MATH_NODE_API, MathNodeDoubleReceiverItem,
                              MathNodeDoubleReceiver);

DECLARE_OBJECT_PROPERTIES_FACTORY(MATH_NODE_API,
                                  MathNodeDoubleEmitterProperties,
                                  MathNodeDoubleEmitter);

#endif  // MATH_NODE_PLUGIN_H
