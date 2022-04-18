/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/string_converter_factory_container.h"
#include "flow/modules/node/converter_factory.h"
#include "flow/plugins/node/converter/string/string_to_boolean_converter.h"
#include "flow/plugins/node/converter/string/string_to_floating_point_converter.h"
#include "flow/plugins/node/converter/string/string_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

StringConverterFactoryContainer::StringConverterFactoryContainer(
  QObject *parent)
    : ConverterFactoryContainer(parent)
{
  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("StringToBoolean"),
    []() { return std::make_unique<StringToBooleanConverter>(); },
    QObject::tr("String -> Boolean"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("StringFloatingPoint"),
    []() { return std::make_unique<StringToFloatingPoint>(); },
    QObject::tr("String -> Floating Point"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    QLatin1String("StringToInteger"),
    []() { return std::make_unique<StringToIntegerConverter>(); },
    QObject::tr("String -> Integer"), QIcon("")));
}

StringConverterFactoryContainer::~StringConverterFactoryContainer() = default;

QString StringConverterFactoryContainer::getName() const
{
  return QObject::tr("Base");
}

QIcon StringConverterFactoryContainer::getIcon() const { return QIcon{}; }
