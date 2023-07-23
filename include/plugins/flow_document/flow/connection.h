#ifndef FLOW_DOCUMENT_CONNECTION_H
#define FLOW_DOCUMENT_CONNECTION_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ConnectionLayer;

class FLOW_DOCUMENT_API Connection : public Object {
  friend ConnectionLayer;

  FLOW_OBJECT_CLASS(Connection, Object)

 public:
  explicit Connection();
  ~Connection() override;

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
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_H