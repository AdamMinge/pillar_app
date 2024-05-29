#ifndef FLOW_DOCUMENT_CONNECTION_CHANGE_EVENT_H
#define FLOW_DOCUMENT_CONNECTION_CHANGE_EVENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/change_event.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class NodeLayer;
class Connection;

/* ------------------------------ ConnectionEvent --------------------------- */

class FLOW_DOCUMENT_API ConnectionEvent : public ChangeEvent {
 public:
  static constexpr QLatin1String type = QLatin1String("ConnectionEvent");

  enum class Event {
    AboutToBeAdded,
    Added,
    Removed,
    AboutToBeRemoved,
  };

 public:
  explicit ConnectionEvent(Event event, NodeLayer* node_layer, qsizetype index);
  ~ConnectionEvent() override;

  [[nodiscard]] Event getEvent() const;
  [[nodiscard]] NodeLayer* getNodeLayer() const;
  [[nodiscard]] qsizetype getIndex() const;
  [[nodiscard]] Connection* getConnection() const;

 private:
  Event m_event;
  NodeLayer* m_node_layer;
  qsizetype m_index;
};

/* --------------------------- ConnectionsChangeEvent ----------------------- */

class FLOW_DOCUMENT_API ConnectionsChangeEvent : public ChangeEvent {
 public:
  static constexpr QLatin1String type = QLatin1String("ConnectionsChangeEvent");

  enum Property : int64_t {
    Name = 1 << 0,
    Visible = 1 << 1,
    Custom = 1 << 5,
  };

 public:
  explicit ConnectionsChangeEvent(QList<Connection*> connections,
                                  Property properties);
  ~ConnectionsChangeEvent() override;

  [[nodiscard]] const QList<Connection*>& getConnections() const;
  [[nodiscard]] Property getProperties() const;

  [[nodiscard]] bool contains(Connection* connection) const;

 private:
  QList<Connection*> m_connections;
  Property m_properties;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_CHANGE_EVENT_H
