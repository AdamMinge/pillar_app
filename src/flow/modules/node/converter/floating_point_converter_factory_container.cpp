/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory.h"
#include "flow/modules/node/converter/floating_point_converter_factory_container.h"
#include "flow/modules/node/converter/floating_point_to_boolean_converter.h"
#include "flow/modules/node/converter/floating_point_to_integer_converter.h"
#include "flow/modules/node/converter/floating_point_to_string_converter.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  FloatingPointConverterFactoryContainer::FloatingPointConverterFactoryContainer(QObject *parent)
      : ConverterFactoryContainer(parent)
  {
    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<FloatingPointToBooleanConverter>(); },
      QObject::tr("Floating Point -> Boolean"), QIcon("")));

    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<FloatingPointToIntegerConverter>(); },
      QObject::tr("Floating Point -> Integer"), QIcon("")));

    addFactory(std::make_unique<ConverterFactory>(
      []() { return std::make_unique<FloatingPointToStringConverter>(); },
      QObject::tr("Floating Point -> String"), QIcon("")));
  }

  FloatingPointConverterFactoryContainer::~FloatingPointConverterFactoryContainer() = default;

  QString FloatingPointConverterFactoryContainer::getName() const
  {
    return QObject::tr("Floating Point");
  }

  QIcon FloatingPointConverterFactoryContainer::getIcon() const { return QIcon{}; }

}// namespace node::converter