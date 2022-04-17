/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_converter_factory_container.h"
#include "flow/modules/node/converter_factory.h"
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
/* -------------------------------------------------------------------------- */

BooleanConverterFactoryContainer::BooleanConverterFactoryContainer(
  QObject *parent)
    : ConverterFactoryContainer(parent)
{
  addFactory(std::make_unique<node::ConverterFactory>(
    []() { return std::make_unique<BooleanToFloatingPointConverter>(); },
    QObject::tr("Boolean -> Floating Point"), QIcon("")));

  addFactory(std::make_unique<node::ConverterFactory>(
    []() { return std::make_unique<BooleanToIntegerConverter>(); },
    QObject::tr("Boolean -> Integer"), QIcon("")));
}

BooleanConverterFactoryContainer::~BooleanConverterFactoryContainer() = default;

QString BooleanConverterFactoryContainer::getName() const
{
  return QObject::tr("Boolean");
}

QIcon BooleanConverterFactoryContainer::getIcon() const { return QIcon{}; }
