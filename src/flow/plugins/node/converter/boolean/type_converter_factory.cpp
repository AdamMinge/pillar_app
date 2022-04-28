/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/type_converter_factory.h"
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

BooleanConverterFactories::BooleanConverterFactories()
    : flow::node::TypeConverterFactories(tr("Boolean"))
{
  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<BooleanToFloatingPointConverter>>(
      tr("Floating Point"), QLatin1String("BooleanToFloatingPoint")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<BooleanToIntegerConverter>>(
      tr("Integer"), QLatin1String("BooleanToInteger")));
}

BooleanConverterFactories::~BooleanConverterFactories() = default;