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
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToBooleanConverter>>(
      tr("Boolean"), QLatin1String("StringToBoolean")));

  registerFactory(std::make_unique<
                  flow::node::BaseTypeConverterFactory<StringToFloatingPoint>>(
    tr("Floating Point"), QLatin1String("StringToFloatingPoint")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<StringToIntegerConverter>>(
      tr("Integer"), QLatin1String("StringToInteger")));
}

StringConverterFactories::~StringConverterFactories() = default;