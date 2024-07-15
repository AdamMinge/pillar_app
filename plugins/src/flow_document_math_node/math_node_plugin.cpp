/* ----------------------------------- Local -------------------------------- */
#include "math_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ MathNodePlugin ---------------------------- */

MathNodePlugin::MathNodePlugin() = default;

MathNodePlugin::~MathNodePlugin() = default;

void MathNodePlugin::init() {
  addObject(new MathNodeAdditionFactory(tr("addition"), tr("Math"), this));
  addObject(new MathNodeDivisionFactory(tr("division"), tr("Math"), this));
  addObject(new MathNodeMultiplicationFactory(tr("multiplication"), tr("Math"),
                                              this));
  addObject(new MathNodeNegationFactory(tr("negation"), tr("Math"), this));
  addObject(
      new MathNodeSubtractionFactory(tr("subtraction"), tr("Math"), this));
  addObject(new MathNodePowerFactory(tr("power"), tr("Math"), this));
  addObject(new MathNodeSquareRootFactory(tr("square root"), tr("Math"), this));
  addObject(new MathNodeEqualFactory(tr("equal"), tr("Math"), this));
  addObject(
      new MathNodeGreaterEqualFactory(tr("greater equal"), tr("Math"), this));
  addObject(new MathNodeGreaterFactory(tr("greater"), tr("Math"), this));
  addObject(new MathNodeLowerEqualFactory(tr("lower equal"), tr("Math"), this));
  addObject(new MathNodeLowerFactory(tr("lower"), tr("Math"), this));
  addObject(new MathNodeNotEqualFactory(tr("not equal"), tr("Math"), this));
  addObject(
      new MathNodeDoubleEmitterFactory(tr("double emitter"), tr("Math"), this));
  addObject(new MathNodeDoubleReceiverFactory(tr("double receiver"), tr("Math"),
                                              this));

  addObject(new MathNodeDoubleEmitterItemFactory(this));
  addObject(new MathNodeDoubleReceiverItemFactory(this));

  addObject(new MathNodeDoubleEmitterPropertiesFactory(this));
}
