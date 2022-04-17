#ifndef FLOW_INTEGER_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_INTEGER_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

class NODE_API IntegerConverterFactoryContainer
    : public node::ConverterFactoryContainer
{
  Q_OBJECT
  Q_INTERFACES(node::ConverterFactoryContainer);
  Q_PLUGIN_METADATA(IID "org.flow.ConverterFactoryContainer" FILE "plugin.json")

public:
  explicit IntegerConverterFactoryContainer(QObject *parent = nullptr);
  ~IntegerConverterFactoryContainer() override;

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
};

#endif//FLOW_INTEGER_CONVERTER_FACTORY_CONTAINER_H
