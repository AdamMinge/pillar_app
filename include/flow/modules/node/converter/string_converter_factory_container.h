#ifndef FLOW_STRING_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_STRING_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API StringConverterFactoryContainer
      : public ConverterFactoryContainer
  {
    Q_OBJECT

  public:
    explicit StringConverterFactoryContainer(QObject *parent = nullptr);
    ~StringConverterFactoryContainer() override;

    [[nodiscard]] QString getName() const override;
    [[nodiscard]] QIcon getIcon() const override;
  };

}// namespace node::converter

#endif//FLOW_STRING_CONVERTER_FACTORY_CONTAINER_H
