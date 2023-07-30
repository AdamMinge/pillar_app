#ifndef FLOW_DOCUMENT_CONNECTION_H
#define FLOW_DOCUMENT_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ConnectionLayer;
class Node;

/* ------------------------------ ConnectionSide ---------------------------- */

class FLOW_DOCUMENT_API ConnectionSide {
 public:
  ConnectionSide(QUuid node_id = {}, size_t pin_id = 0);
  ~ConnectionSide();

  void setNodeId(const QUuid &id);
  [[nodiscard]] QUuid getNodeId() const;

  void setPinId(size_t id);
  [[nodiscard]] size_t getPinId() const;

  void serialize(utils::OArchive &archive) const;
  void deserialize(utils::IArchive &archive);

 private:
  QUuid m_node_id;
  size_t m_pin_id;
};

/* --------------------------------- Connection ----------------------------- */

class FLOW_DOCUMENT_API Connection : public Object {
  friend ConnectionLayer;

  FLOW_OBJECT_CLASS(Connection, Object)

 public:
  explicit Connection();
  ~Connection() override;

  void setOutputSide(ConnectionSide connection_side);
  void setInputSide(ConnectionSide connection_side);

  const ConnectionSide &getOutputSide() const;
  const ConnectionSide &getInputSide() const;

  void setVisible(bool visible);
  [[nodiscard]] bool isVisible() const;

  [[nodiscard]] ConnectionLayer *getParent() const;

  [[nodiscard]] std::unique_ptr<Connection> clone() const;

  void serialize(utils::OArchive &archive) const override;
  void deserialize(utils::IArchive &archive) override;

 protected:
  void init(const Connection *connection);
  void setParent(ConnectionLayer *parent);

 private:
  ConnectionLayer *m_parent;
  bool m_visible;

  ConnectionSide m_output_side;
  ConnectionSide m_input_side;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_H