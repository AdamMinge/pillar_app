#ifndef FLOW_DOCUMENT_ADD_REMOVE_CONNECTION_H
#define FLOW_DOCUMENT_ADD_REMOVE_CONNECTION_H

/* ---------------------------------- Standard ------------------------------ */
#include <list>
#include <memory>
/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class NodeLayer;
class Connection;

/* ------------------------------ ConnectionEntry --------------------------- */

struct FLOW_DOCUMENT_API ConnectionEntry {
 public:
  explicit ConnectionEntry(ConnectionEntry&& other);
  explicit ConnectionEntry(NodeLayer* node_layer, qsizetype index);
  explicit ConnectionEntry(NodeLayer* node_layer,
                           std::unique_ptr<Connection> new_connection,
                           qsizetype index);
  ~ConnectionEntry();

 public:
  NodeLayer* node_layer;
  std::unique_ptr<Connection> new_connection;
  qsizetype index;
};

/* ---------------------------- AddRemoveConnections ------------------------ */

class FLOW_DOCUMENT_API AddRemoveConnections : public pillar::Command {
 public:
  explicit AddRemoveConnections(const QString& name, FlowDocument* document,
                                std::list<ConnectionEntry> entries,
                                Command* parent = nullptr);
  ~AddRemoveConnections() override;

 protected:
  void addConnection();
  void removeConnection();

 protected:
  FlowDocument* m_document;
  std::list<ConnectionEntry> m_entries;
};

/* ------------------------------- AddConnections --------------------------- */

class FLOW_DOCUMENT_API AddConnections : public AddRemoveConnections {
 public:
  explicit AddConnections(FlowDocument* document,
                          std::list<ConnectionEntry> entries,
                          Command* parent = nullptr);
  ~AddConnections() override;

  void undo() override;
  void redo() override;
};

/* ------------------------------ RemoveConnections ------------------------- */

class FLOW_DOCUMENT_API RemoveConnections : public AddRemoveConnections {
 public:
  RemoveConnections(FlowDocument* document, std::list<ConnectionEntry> entries,
                    Command* parent = nullptr);
  ~RemoveConnections() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_ADD_REMOVE_CONNECTION_H