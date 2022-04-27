/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/type_converter_factory.h"
#include "flow/plugins/node/converter/string/string_to_boolean_converter.h"
#include "flow/plugins/node/converter/string/string_to_floating_point_converter.h"
#include "flow/plugins/node/converter/string/string_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

StringConverterFactories::StringConverterFactories()
    : flow::node::TypeConverterFactories(tr("String"), QIcon(""))
{
  registerFactory(
    QLatin1String("StringToBoolean"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToBooleanConverter>>(
      tr("String -> Boolean"), QIcon("")));

  registerFactory(
    QLatin1String("StringToFloatingPoint"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToFloatingPoint>>(
      tr("String -> Floating Point"), QIcon("")));

  registerFactory(
    QLatin1String("StringToInteger"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToIntegerConverter>>(
      tr("String -> Integer"), QIcon("")));
}

StringConverterFactories::~StringConverterFactories() = default;