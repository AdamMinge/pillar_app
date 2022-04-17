/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/connection.h"
#include "flow/modules/node/node_data.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  Connection::Connection(Pin &out, Pin &in)
      : m_in(in), m_out(out), m_converter(nullptr)
  {
    connect(&m_out, &Pin::dataChanged, this, &Connection::transferData);
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
    if (m_converter == converter) return;

    m_converter = std::move(converter);
    Q_EMIT converterChanged(m_converter);
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

}// namespace node