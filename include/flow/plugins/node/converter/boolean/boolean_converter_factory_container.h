#ifndef FLOW_BOOLEAN_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_BOOLEAN_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

class NODE_API BooleanConverterFactoryContainer
    : public node::ConverterFactoryContainer
{
  Q_OBJECT
  Q_INTERFACES(node::ConverterFactoryContainer);

public:
  explicit BooleanConverterFactoryContainer(QObject *parent = nullptr);
  ~BooleanConverterFactoryContainer() override;

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
};

#endif//FLOW_BOOLEAN_CONVERTER_FACTORY_CONTAINER_H
