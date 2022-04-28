#ifndef FLOW_CONNECTION_H
#define FLOW_CONNECTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  class TypeConverter;

  class LIB_FLOW_API Connection : public QObject
  {
    Q_OBJECT

  public:
    explicit Connection(Pin &out, Pin &in);
    ~Connection() override;

    [[nodiscard]] const Pin &getPin(Pin::Type type) const;
    [[nodiscard]] Pin &getPin(Pin::Type type);

    void setConverter(std::shared_ptr<TypeConverter> converter);
    [[nodiscard]] std::shared_ptr<TypeConverter> getConverter() const;

  Q_SIGNALS:
    void converterChanged(std::shared_ptr<flow::node::TypeConverter> converter);

  private Q_SLOTS:
    void transferData(const flow::node::NodeData &data);

  private:
    Pin &m_in;
    Pin &m_out;
    std::shared_ptr<TypeConverter> m_converter;
  };

}// namespace flow::node

#endif//FLOW_CONNECTION_H
