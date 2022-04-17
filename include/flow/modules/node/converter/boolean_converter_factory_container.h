#ifndef FLOW_BOOLEAN_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_BOOLEAN_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API BooleanConverterFactoryContainer
      : public ConverterFactoryContainer
  {
    Q_OBJECT

  public:
    explicit BooleanConverterFactoryContainer(QObject *parent = nullptr);
    ~BooleanConverterFactoryContainer() override;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] QIcon getIcon() const override;
  };

}// namespace node::converter

#endif//FLOW_BOOLEAN_CONVERTER_FACTORY_CONTAINER_H
