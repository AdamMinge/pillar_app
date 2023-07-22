#ifndef FLOW_DOCUMENT_CONNECTION_LAYER_H
#define FLOW_DOCUMENT_CONNECTION_LAYER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/serialization/object_unique_ptr.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API ConnectionLayer : public Layer {
  FLOW_OBJECT_CLASS(ConnectionLayer, Layer)

 public:
  using Connections = std::vector<ObjectUniquePtr<Connection>>;

 public:
  explicit ConnectionLayer();
  ~ConnectionLayer() override;

  void append(std::unique_ptr<Connection> connection);
  void insert(qsizetype index, std::unique_ptr<Connection> connection);
  void remove(qsizetype index);

  [[nodiscard]] std::unique_ptr<Connection> take(qsizetype index);
  [[nodiscard]] Connection* at(qsizetype index) const;
  [[nodiscard]] qsizetype indexOf(Connection* connection) const;

  [[nodiscard]] qsizetype size() const;

  Connections::iterator begin();
  Connections::iterator end();

  Connections::const_iterator begin() const;
  Connections::const_iterator end() const;

  [[nodiscard]] std::unique_ptr<Layer> clone() const override;

  void serialize(utils::OArchive& archive) const override;
  void deserialize(utils::IArchive& archive) override;

 protected:
  void init(const ConnectionLayer* connection_layer);

 private:
  Connections m_connections;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_LAYER_H