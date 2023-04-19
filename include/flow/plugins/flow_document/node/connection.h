#ifndef FLOW_CONNECTION_H
#define FLOW_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
#include "flow/plugins/flow_document/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class TypeConverter;

class FLOW_DOCUMENT_API Connection {
 public:
  explicit Connection(Pin &out, Pin &in);
  ~Connection();

  [[nodiscard]] const Pin &getPin(Pin::Type type) const;
  [[nodiscard]] Pin &getPin(Pin::Type type);

  void setConverter(std::shared_ptr<TypeConverter> converter);
  [[nodiscard]] std::shared_ptr<TypeConverter> getConverter() const;

 private:
  void transferData(const NodeData &data);

 private:
  Pin &m_in;
  Pin &m_out;
  std::shared_ptr<TypeConverter> m_converter;
};

}  // namespace plugin::flow_document

#endif  // FLOW_CONNECTION_H
