/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/string_converter_factory_container.h"
#include "flow/modules/node/converter/converter_factory.h"
#include "flow/modules/node/converter/string_to_boolean_converter.h"
#include "flow/modules/node/converter/string_to_floating_point_converter.h"
#include "flow/modules/node/converter/string_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  StringConverterFactoryContainer::StringConverterFactoryContainer(
    QObject *parent)
      : ConverterFactoryContainer(parent)
  {
    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<StringToBooleanConverter>(); },
      QObject::tr("String -> Boolean"), QIcon("")));

    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<StringToFloatingPoint>(); },
      QObject::tr("String -> Floating Point"), QIcon("")));

    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<StringToIntegerConverter>(); },
      QObject::tr("String -> Integer"), QIcon("")));
  }

  StringConverterFactoryContainer::~StringConverterFactoryContainer() = default;

  QString StringConverterFactoryContainer::getName() const
  {
    return QObject::tr("Base");
  }

  QIcon StringConverterFactoryContainer::getIcon() const { return QIcon{}; }

}// namespace node::converter