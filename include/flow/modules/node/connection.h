#ifndef FLOW_CONNECTION_H
#define FLOW_CONNECTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  class TypeConverter;

  class NODE_API Connection : public QObject
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
    void converterChanged(std::shared_ptr<TypeConverter> converter);

  private Q_SLOTS:
    void transferData(const node::NodeData &data);

  private:
    Pin &m_in;
    Pin &m_out;
    std::shared_ptr<TypeConverter> m_converter;
  };

}// namespace node

#endif//FLOW_CONNECTION_H
