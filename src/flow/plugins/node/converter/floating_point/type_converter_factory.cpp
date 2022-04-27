/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_boolean_converter.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_integer_converter.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_string_converter.h"
#include "flow/plugins/node/converter/floating_point/type_converter_factory.h"
/* -------------------------------------------------------------------------- */

FloatingPointConverterFactories::FloatingPointConverterFactories()
    : flow::node::TypeConverterFactories(tr("Floating Point"), QIcon(""))
{
  registerFactory(
    QLatin1String("FloatingPointToInteger"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToIntegerConverter>>(
      tr("Floating Point -> Integer"), QIcon("")));

  registerFactory(
    QLatin1String("FloatingPointToString"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToStringConverter>>(
      tr("Floating Point -> String"), QIcon("")));

  registerFactory(
    QLatin1String("FloatingPointToBoolean"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToBooleanConverter>>(
      tr("Floating Point -> Boolean"), QIcon("")));
}

FloatingPointConverterFactories::~FloatingPointConverterFactories() = default;