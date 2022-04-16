#ifndef FLOW_BASE_CONVERTER_FACTORY_CONTAINER_H
#define FLOW_BASE_CONVERTER_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/converter_factory_container.h"
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  class NODE_API BaseConverterFactoryContainer
      : public ConverterFactoryContainer
  {
    Q_OBJECT

  public:
    explicit BaseConverterFactoryContainer();
    ~BaseConverterFactoryContainer() override;
  };

}// namespace node::converter

#endif//FLOW_BASE_CONVERTER_FACTORY_CONTAINER_H
