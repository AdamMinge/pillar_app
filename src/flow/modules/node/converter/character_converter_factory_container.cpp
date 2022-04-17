/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory.h"
#include "flow/modules/node/converter/character_converter_factory_container.h"
#include "flow/modules/node/converter/character_to_boolean_converter.h"
#include "flow/modules/node/converter/character_to_integer_converter.h"
#include "flow/modules/node/converter/character_to_string_converter.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  CharacterConverterFactoryContainer::CharacterConverterFactoryContainer(QObject *parent)
      : ConverterFactoryContainer(parent)
  {
    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<CharacterToBooleanConverter>(); },
      QObject::tr("Character -> Boolean"), QIcon("")));

    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<CharacterToIntegerConverter>(); },
      QObject::tr("Character -> Integer"), QIcon("")));

    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<CharacterToStringConverter>(); },
      QObject::tr("Character -> String"), QIcon("")));
  }

  CharacterConverterFactoryContainer::~CharacterConverterFactoryContainer() = default;

  QString CharacterConverterFactoryContainer::getName() const
  {
    return QObject::tr("Character");
  }

  QIcon CharacterConverterFactoryContainer::getIcon() const { return QIcon{}; }

}// namespace node::converter