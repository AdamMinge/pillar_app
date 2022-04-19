/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/converter_plugin.h"
#include "flow/plugins/node/converter/string/string_to_boolean_converter.h"
#include "flow/plugins/node/converter/string/string_to_floating_point_converter.h"
#include "flow/plugins/node/converter/string/string_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

TypeConverter::TypeConverter()
    : m_string_to_boolean_converter(new StringToBooleanConverter),
      m_string_to_floating_point_converter(new StringToFloatingPoint),
      m_string_to_integer_converter(new StringToIntegerConverter)
{
  addObject(m_string_to_boolean_converter.get());
  addObject(m_string_to_floating_point_converter.get());
  addObject(m_string_to_integer_converter.get());
}

TypeConverter::~TypeConverter() = default;