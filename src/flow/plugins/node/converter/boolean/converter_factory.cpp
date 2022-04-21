/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
#include "flow/plugins/node/converter/boolean/converter_factory.h"
/* -------------------------------------------------------------------------- */

BooleanConverterFactories::BooleanConverterFactories()
    : flow::node::ConverterFactories(tr("Boolean"), QIcon(""))
{
  registerFactory(
    QLatin1String("BooleanToFloatingPoint"),
    std::make_unique<
      flow::node::BaseConverterFactory<BooleanToFloatingPointConverter>>(
      tr("Boolean -> Floating Point"), QIcon("")));

  registerFactory(
    QLatin1String("BooleanToInteger"),
    std::make_unique<
      flow::node::BaseConverterFactory<BooleanToIntegerConverter>>(
      tr("Boolean -> Integer"), QIcon("")));
}

BooleanConverterFactories::~BooleanConverterFactories() = default;