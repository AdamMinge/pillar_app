#ifndef FLOW_TYPE_CONVERTER_H
#define FLOW_TYPE_CONVERTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
/* -------------------------------------------------------------------------- */

namespace node::data
{
  class NodeData;
}

namespace node::converter
{

  class NODE_API TypeConverter : public QObject
  {
    Q_OBJECT

  public:
    explicit TypeConverter() = default;
    ~TypeConverter() override = default;

    [[nodiscard]] virtual std::unique_ptr<data::NodeData>
    convert(const data::NodeData &data) = 0;
  };

}// namespace node::converter

Q_DECLARE_INTERFACE(node::converter::TypeConverter, "org.flow.TypeConverter")

#endif//FLOW_TYPE_CONVERTER_H
