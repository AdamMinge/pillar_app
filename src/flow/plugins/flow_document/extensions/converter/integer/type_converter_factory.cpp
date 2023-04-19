/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/type_converter_factory.h"
#include "flow/plugins/node/converter/integer/integer_to_boolean_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_character_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_floating_point_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_string_converter.h"
/* -------------------------------------------------------------------------- */

IntegerConverterFactories::IntegerConverterFactories()
    : flow::node::TypeConverterFactories(tr("Integer"))
{
  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToCharacterConverter>>(
      tr("Character"), QLatin1String("IntegerToCharacter")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToFloatingPointConverter>>(
      tr("Floating Point"), QLatin1String("IntegerToFloatingPoint")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToStringConverter>>(
      tr("String"), QLatin1String("IntegerToString")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<IntegerToBooleanConverter>>(
      tr("Boolean"), QLatin1String("IntegerToBoolean")));
}

IntegerConverterFactories::~IntegerConverterFactories() = default;