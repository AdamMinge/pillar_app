/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/converter_plugin.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_boolean_converter.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_integer_converter.h"
#include "flow/plugins/node/converter/floating_point/floating_point_to_string_converter.h"
/* -------------------------------------------------------------------------- */

TypeConverter::TypeConverter()
    : m_floating_point_to_boolean_converter(
        new FloatingPointToBooleanConverter),
      m_floating_point_to_string_converter(new FloatingPointToStringConverter),
      m_floating_point_to_integer_converter(new FloatingPointToIntegerConverter)
{
  addObject(m_floating_point_to_boolean_converter.get());
  addObject(m_floating_point_to_string_converter.get());
  addObject(m_floating_point_to_integer_converter.get());
}

TypeConverter::~TypeConverter() = default;