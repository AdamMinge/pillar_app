/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/integer_to_boolean_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_character_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_floating_point_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_string_converter.h"
#include "flow/plugins/node/converter/integer/type_converter_factory.h"
/* -------------------------------------------------------------------------- */

IntegerConverterFactories::IntegerConverterFactories()
    : flow::node::TypeConverterFactories(tr("Integer"), QIcon(""))
{
  registerFactory(
    QLatin1String("IntegerToCharacter"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToCharacterConverter>>(
      tr("Integer -> Character"), QIcon("")));

  registerFactory(
    QLatin1String("IntegerToFloatingPoint"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToFloatingPointConverter>>(
      tr("Integer -> Floating Point"), QIcon("")));

  registerFactory(
    QLatin1String("IntegerToString"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToStringConverter>>(
      tr("Integer -> String"), QIcon("")));

  registerFactory(
    QLatin1String("IntegerToBoolean"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToBooleanConverter>>(
      tr("Integer -> Boolean"), QIcon("")));
}

IntegerConverterFactories::~IntegerConverterFactories() = default;