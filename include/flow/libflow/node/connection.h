#ifndef FLOW_CONNECTION_H
#define FLOW_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/pin.h"
#include "flow/libflow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class TypeConverter;

  class LIB_FLOW_API Connection : public Object
  {
  public:
    explicit Connection(Pin &out, Pin &in);
    ~Connection() override;

    [[nodiscard]] const Pin &getPin(Pin::Type type) const;
    [[nodiscard]] Pin &getPin(Pin::Type type);

    void setConverter(std::shared_ptr<TypeConverter> converter);
    [[nodiscard]] std::shared_ptr<TypeConverter> getConverter() const;

  private:
    void transferData(const flow::node::NodeData &data);

  private:
    Pin &m_in;
    Pin &m_out;
    std::shared_ptr<TypeConverter> m_converter;
  };

}// namespace flow::node

#endif//FLOW_CONNECTION_H
