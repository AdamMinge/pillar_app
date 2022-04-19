#ifndef FLOW_TYPE_CONVERTER_H
#define FLOW_TYPE_CONVERTER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtPlugin>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class NodeData;

  class LIB_FLOW_API TypeConverter : public QObject
  {
    Q_OBJECT

  public:
    explicit TypeConverter() = default;
    virtual ~TypeConverter() = default;

    [[nodiscard]] virtual std::unique_ptr<NodeData>
    convert(const NodeData &data) = 0;
  };

}// namespace flow::node

#endif//FLOW_TYPE_CONVERTER_H
