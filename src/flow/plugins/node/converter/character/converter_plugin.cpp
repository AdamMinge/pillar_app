/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/converter_plugin.h"
#include "flow/plugins/node/converter/character/character_to_boolean_converter.h"
#include "flow/plugins/node/converter/character/character_to_integer_converter.h"
#include "flow/plugins/node/converter/character/character_to_string_converter.h"
/* -------------------------------------------------------------------------- */

TypeConverter::TypeConverter()
    : m_character_to_string_converter(new CharacterToStringConverter),
      m_character_to_integer_converter(new CharacterToIntegerConverter),
      m_character_to_boolean_converter(new CharacterToBooleanConverter)
{
  addObject(m_character_to_string_converter.get());
  addObject(m_character_to_integer_converter.get());
  addObject(m_character_to_boolean_converter.get());
}

TypeConverter::~TypeConverter() = default;