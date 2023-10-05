#ifndef MATH_NODE_PLUGIN_H
#define MATH_NODE_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "math_node_addition.h"
#include "math_node_division.h"
#include "math_node_multiplication.h"
#include "math_node_negation.h"
#include "math_node_power.h"
#include "math_node_square_root.h"
#include "math_node_subtraction.h"
#include "math_node_value.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodePlugin : public egnite::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(egnite::PluginInterface)
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
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeFloatEmitter)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeFloatReceiver)

#endif  // MATH_NODE_PLUGIN_H
