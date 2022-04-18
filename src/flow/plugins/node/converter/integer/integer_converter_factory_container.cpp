/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/integer_converter_factory_container.h"
#include "flow/modules/node/converter_factory.h"
#include "flow/plugins/node/converter/integer/integer_to_boolean_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_character_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_floating_point_converter.h"
#include "flow/plugins/node/converter/integer/integer_to_string_converter.h"
/* -------------------------------------------------------------------------- */

IntegerConverterFactoryContainer::IntegerConverterFactoryContainer(
  QObject *parent)
    : ConverterFactoryContainer(parent)
{
  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("IntegerToBoolean"),
    []() { return std::make_unique<IntegerToBooleanConverter>(); },
    QObject::tr("Integer -> Boolean"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("IntegerToCharacter"),
    []() { return std::make_unique<IntegerToCharacterConverter>(); },
    QObject::tr("Integer -> Character"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("IntegerToFloatingPoint"),
    []() { return std::make_unique<IntegerToFloatingPointConverter>(); },
    QObject::tr("Integer -> Floating Point"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("IntegerToString"),
    []() { return std::make_unique<IntegerToStringConverter>(); },
    QObject::tr("Integer -> String"), QIcon("")));
}

IntegerConverterFactoryContainer::~IntegerConverterFactoryContainer() = default;

QString IntegerConverterFactoryContainer::getName() const
{
  return QObject::tr("Integer");
}

QIcon IntegerConverterFactoryContainer::getIcon() const { return QIcon{}; }
