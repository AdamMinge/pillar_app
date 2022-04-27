/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
#include "flow/plugins/node/converter/boolean/type_converter_factory.h"
/* -------------------------------------------------------------------------- */

BooleanConverterFactories::BooleanConverterFactories()
    : flow::node::TypeConverterFactories(tr("Boolean"))
{
  registerFactory(
    QLatin1String("BooleanToFloatingPoint"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<BooleanToFloatingPointConverter>>(
      tr("Floating Point")));

  registerFactory(
    QLatin1String("BooleanToInteger"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<BooleanToIntegerConverter>>(
      tr("Integer")));
}

BooleanConverterFactories::~BooleanConverterFactories() = default;