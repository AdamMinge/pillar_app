/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/connection.h"
#include "flow/libflow/node/node_data.h"
#include "flow/libflow/node/type_converter.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  Connection::Connection(Pin &out, Pin &in)
      : m_in(in), m_out(out), m_converter(nullptr)
  {
    out.addListener([this](auto&& data){
      this->transferData(std::forward<decltype(data)>(data));
    });
  }

  Connection::~Connection() = default;

  const Pin &Connection::getPin(Pin::Type type) const
  {
    return type == Pin::Type::In ? m_in : m_out;
  }

  Pin &Connection::getPin(Pin::Type type)
  {
    return type == Pin::Type::In ? m_in : m_out;
  }

  void Connection::setConverter(std::shared_ptr<TypeConverter> converter)
  {
    m_converter = std::move(converter);
  }

  std::shared_ptr<TypeConverter> Connection::getConverter() const
  {
    return m_converter;
  }

  void Connection::transferData(const NodeData &data)
  {
    if (m_converter)
    {
      auto converted_data = m_converter->convert(data);
      if (converted_data) m_in.setData(*converted_data);
    } else
    {
      m_in.setData(data);
    }
  }

}// namespace flow::node