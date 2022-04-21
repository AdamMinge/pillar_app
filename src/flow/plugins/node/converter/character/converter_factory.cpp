/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_to_boolean_converter.h"
#include "flow/plugins/node/converter/character/character_to_integer_converter.h"
#include "flow/plugins/node/converter/character/character_to_string_converter.h"
#include "flow/plugins/node/converter/character/converter_factory.h"
/* -------------------------------------------------------------------------- */

CharacterConverterFactories::CharacterConverterFactories()
    : flow::node::ConverterFactories(tr("Character"), QIcon(""))
{
  registerFactory(
    QLatin1String("CharacterToBoolean"),
    std::make_unique<
      flow::node::BaseConverterFactory<CharacterToBooleanConverter>>(
      tr("Character -> Boolean"), QIcon("")));

  registerFactory(
    QLatin1String("CharacterToInteger"),
    std::make_unique<
      flow::node::BaseConverterFactory<CharacterToIntegerConverter>>(
      tr("Character -> Integer"), QIcon("")));

  registerFactory(
    QLatin1String("CharacterToString"),
    std::make_unique<
      flow::node::BaseConverterFactory<CharacterToStringConverter>>(
      tr("Character -> String"), QIcon("")));
}

CharacterConverterFactories::~CharacterConverterFactories() = default;