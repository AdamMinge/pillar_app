/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/converter_plugin.h"
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

TypeConverter::TypeConverter()
    : m_boolean_to_integer_converter(new BooleanToIntegerConverter),
      m_boolean_to_floating_point_converter(new BooleanToFloatingPointConverter)
{
  addObject(m_boolean_to_integer_converter.get());
  addObject(m_boolean_to_floating_point_converter.get());
}

TypeConverter::~TypeConverter() = default;