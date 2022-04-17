/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_converter_factory_container.h"
#include "flow/modules/node/converter_factory.h"
#include "flow/plugins/node/converter/character/character_to_boolean_converter.h"
#include "flow/plugins/node/converter/character/character_to_integer_converter.h"
#include "flow/plugins/node/converter/character/character_to_string_converter.h"
/* -------------------------------------------------------------------------- */

CharacterConverterFactoryContainer::CharacterConverterFactoryContainer(
  QObject *parent)
    : ConverterFactoryContainer(parent)
{
  addFactory(std::make_unique<node::ConverterFactory>(
    []() { return std::make_unique<CharacterToBooleanConverter>(); },
    QObject::tr("Character -> Boolean"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    []() { return std::make_unique<CharacterToIntegerConverter>(); },
    QObject::tr("Character -> Integer"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    []() { return std::make_unique<CharacterToStringConverter>(); },
    QObject::tr("Character -> String"), QIcon("")));
}

CharacterConverterFactoryContainer::~CharacterConverterFactoryContainer() =
  default;

QString CharacterConverterFactoryContainer::getName() const
{
  return QObject::tr("Character");
}

QIcon CharacterConverterFactoryContainer::getIcon() const { return QIcon{}; }
