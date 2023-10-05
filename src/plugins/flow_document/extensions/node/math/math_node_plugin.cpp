/* ----------------------------------- Local -------------------------------- */
#include "math_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ MathNodePlugin ---------------------------- */

MathNodePlugin::MathNodePlugin() = default;

MathNodePlugin::~MathNodePlugin() = default;

void MathNodePlugin::init() {
  addObject(new MathNodeAdditionFactory(tr("Addition"), tr("Math"), this));
  addObject(new MathNodeDivisionFactory(tr("Division"), tr("Math"), this));
  addObject(new MathNodeMultiplicationFactory(tr("Multiplication"), tr("Math"),
                                              this));
  addObject(new MathNodeNegationFactory(tr("Negation"), tr("Math"), this));
  addObject(
      new MathNodeSubtractionFactory(tr("Subtraction"), tr("Math"), this));
  addObject(new MathNodePowerFactory(tr("Power"), tr("Math"), this));
  addObject(new MathNodeSquareRootFactory(tr("Square Root"), tr("Math"), this));
  addObject(
      new MathNodeFloatEmitterFactory(tr("Float Emitter"), tr("Math"), this));
  addObject(
      new MathNodeFloatReceiverFactory(tr("Float Receiver"), tr("Math"), this));
}
