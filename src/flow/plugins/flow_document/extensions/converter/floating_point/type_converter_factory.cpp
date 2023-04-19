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
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToIntegerConverter>>(
      tr("Integer"), QLatin1String("FloatingPointToInteger")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToStringConverter>>(
      tr("String"), QLatin1String("FloatingPointToString")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<FloatingPointToBooleanConverter>>(
      tr("Boolean"), QLatin1String("FloatingPointToBoolean")));
}

FloatingPointConverterFactories::~FloatingPointConverterFactories() = default;