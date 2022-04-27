/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/type_converter_factory.h"
#include "flow/plugins/node/converter/string/string_to_boolean_converter.h"
#include "flow/plugins/node/converter/string/string_to_floating_point_converter.h"
#include "flow/plugins/node/converter/string/string_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

StringConverterFactories::StringConverterFactories()
    : flow::node::TypeConverterFactories(tr("String"))
{
  registerFactory(
    QLatin1String("StringToBoolean"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToBooleanConverter>>(
      tr("Boolean")));

  registerFactory(
    QLatin1String("StringToFloatingPoint"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToFloatingPoint>>(
      tr("Floating Point")));

  registerFactory(
    QLatin1String("StringToInteger"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToIntegerConverter>>(
      tr("Integer")));
}

StringConverterFactories::~StringConverterFactories() = default;