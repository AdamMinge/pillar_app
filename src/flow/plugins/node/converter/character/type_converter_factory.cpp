/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/type_converter_factory.h"
#include "flow/plugins/node/converter/character/character_to_boolean_converter.h"
#include "flow/plugins/node/converter/character/character_to_integer_converter.h"
#include "flow/plugins/node/converter/character/character_to_string_converter.h"
/* -------------------------------------------------------------------------- */

CharacterConverterFactories::CharacterConverterFactories()
    : flow::node::TypeConverterFactories(tr("Character"))
{
  registerFactory(
    QLatin1String("CharacterToBoolean"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<CharacterToBooleanConverter>>(
      tr("Boolean")));

  registerFactory(
    QLatin1String("CharacterToInteger"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<CharacterToIntegerConverter>>(
      tr("Integer")));

  registerFactory(
    QLatin1String("CharacterToString"),
    std::make_unique<
      flow::node::BaseTypeConverterFactory<CharacterToStringConverter>>(
      tr("String")));
}

CharacterConverterFactories::~CharacterConverterFactories() = default;