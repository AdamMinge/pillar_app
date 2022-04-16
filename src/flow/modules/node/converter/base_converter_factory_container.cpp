/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/base_converter_factory_container.h"
#include "flow/modules/node/converter/converter_factory.h"

#include "flow/modules/node/converter/boolean_to_floating_point_converter.h"
#include "flow/modules/node/converter/boolean_to_integer_converter.h"
#include "flow/modules/node/converter/character_to_boolean_converter.h"
#include "flow/modules/node/converter/character_to_integer_converter.h"
#include "flow/modules/node/converter/character_to_string_converter.h"
#include "flow/modules/node/converter/floating_point_to_boolean_converter.h"
#include "flow/modules/node/converter/floating_point_to_integer_converter.h"
#include "flow/modules/node/converter/floating_point_to_string_converter.h"
#include "flow/modules/node/converter/integer_to_boolean_converter.h"
#include "flow/modules/node/converter/integer_to_character_converter.h"
#include "flow/modules/node/converter/integer_to_floating_point_converter.h"
#include "flow/modules/node/converter/integer_to_string_converter.h"
#include "flow/modules/node/converter/string_to_boolean_converter.h"
#include "flow/modules/node/converter/string_to_floating_point_converter.h"
#include "flow/modules/node/converter/string_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

#define ADD_FACTORY(TYPE, NAME, ICON)                                          \
  addFactory(std::make_unique<ConverterFactory>(                               \
    []() { return std::make_unique<TYPE>(); }, QObject::tr(NAME),              \
    QIcon(ICON)))

namespace node::converter
{

  BaseConverterFactoryContainer::BaseConverterFactoryContainer(QObject *parent)
      : ConverterFactoryContainer(parent)
  {
    ADD_FACTORY(
      BooleanToFloatingPointConverter, "Boolean -> Floating Point", "");
    ADD_FACTORY(BooleanToIntegerConverter, "Boolean -> Integer", "");

    ADD_FACTORY(CharacterToBooleanConverter, "Character -> Boolean", "");
    ADD_FACTORY(CharacterToIntegerConverter, "Character -> Integer", "");
    ADD_FACTORY(CharacterToStringConverter, "Character -> String", "");

    ADD_FACTORY(
      FloatingPointToBooleanConverter, "Floating Point -> Boolean", "");
    ADD_FACTORY(
      FloatingPointToIntegerConverter, "Floating Point -> Integer", "");
    ADD_FACTORY(FloatingPointToStringConverter, "Floating Point -> String", "");

    ADD_FACTORY(IntegerToBooleanConverter, "Integer -> Boolean", "");
    ADD_FACTORY(IntegerToCharacterConverter, "Integer -> Character", "");
    ADD_FACTORY(
      IntegerToFloatingPointConverter, "Integer -> Floating Point", "");
    ADD_FACTORY(IntegerToStringConverter, "Integer -> String", "");

    ADD_FACTORY(StringToBooleanConverter, "String -> Boolean", "");
    ADD_FACTORY(StringToFloatingPoint, "String -> Floating Point", "");
    ADD_FACTORY(StringToIntegerConverter, "String -> Integer", "");
  }

  BaseConverterFactoryContainer::~BaseConverterFactoryContainer() = default;

  QString BaseConverterFactoryContainer::getName() const
  {
    return QObject::tr("Base");
  }

  QIcon BaseConverterFactoryContainer::getIcon() const { return QIcon{}; }

}// namespace node::converter