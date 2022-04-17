#ifndef FLOW_INTEGER_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_INTEGER_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API IntegerConverterFactoryContainer
      : public ConverterFactoryContainer
  {
    Q_OBJECT

  public:
    explicit IntegerConverterFactoryContainer(QObject *parent = nullptr);
    ~IntegerConverterFactoryContainer() override;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] QIcon getIcon() const override;
  };

}// namespace node::converter

#endif//FLOW_INTEGER_CONVERTER_FACTORY_CONTAINER_H
