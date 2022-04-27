/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/type_converter_factory.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_boolean_converter.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_integer_converter.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_string_converter.h"
/* -------------------------------------------------------------------------- */

FloatingPointConverterFactories::FloatingPointConverterFactories()
    : flow::node::TypeConverterFactories(tr("Floating Point"))
{
  registerFactory(
    QLatin1String("FloatingPointToInteger"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToIntegerConverter>>(
      tr("Integer")));

  registerFactory(
    QLatin1String("FloatingPointToString"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToStringConverter>>(
      tr("String")));

  registerFactory(
    QLatin1String("FloatingPointToBoolean"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToBooleanConverter>>(
      tr("Boolean")));
}

FloatingPointConverterFactories::~FloatingPointConverterFactories() = default;