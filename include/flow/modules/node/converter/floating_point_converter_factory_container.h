#ifndef FLOW_FLOATING_POINT_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_FLOATING_POINT_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API FloatingPointConverterFactoryContainer
      : public ConverterFactoryContainer
  {
    Q_OBJECT
    Q_INTERFACES(node::converter::ConverterFactoryContainer);

  public:
    explicit FloatingPointConverterFactoryContainer(QObject *parent = nullptr);
    ~FloatingPointConverterFactoryContainer() override;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] QIcon getIcon() const override;
  };

}// namespace node::converter

#endif//FLOW_FLOATING_POINT_CONVERTER_FACTORY_CONTAINER_H
