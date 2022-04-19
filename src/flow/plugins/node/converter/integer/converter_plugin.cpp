/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/converter_plugin.h"
#include "flow/plugins/node/converter/integer/integer_to_boolean_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_character_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_floating_point_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_string_converter.h"
/* -------------------------------------------------------------------------- */

TypeConverter::TypeConverter()
    : m_integer_to_boolean_converter(new IntegerToBooleanConverter),
      m_integer_to_string_converter(new IntegerToStringConverter),
      m_integer_to_floating_point_converter(
        new IntegerToFloatingPointConverter),
      m_integer_to_character_converter(new IntegerToCharacterConverter)
{
  addObject(m_integer_to_boolean_converter.get());
  addObject(m_integer_to_string_converter.get());
  addObject(m_integer_to_floating_point_converter.get());
  addObject(m_integer_to_character_converter.get());
}

TypeConverter::~TypeConverter() = default;