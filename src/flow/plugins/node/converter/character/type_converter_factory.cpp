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
    std::make_unique<
      flow::node::BaseTypeConverterFactory<CharacterToBooleanConverter>>(
      tr("Boolean"), QLatin1String("CharacterToBoolean")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<CharacterToIntegerConverter>>(
      tr("Integer"), QLatin1String("CharacterToInteger")));

  registerFactory(
    std::make_unique<
      flow::node::BaseTypeConverterFactory<CharacterToStringConverter>>(
      tr("String"), QLatin1String("CharacterToString")));
}

CharacterConverterFactories::~CharacterConverterFactories() = default;