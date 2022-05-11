#ifndef FLOW_FLOW_DOCUMENT_H
#define FLOW_FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointer>
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/document/document.h"
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}// namespace flow::node

class ObjectsChangedPropertiesEvent;
class ObjectsAddedEvent;
class ObjectsRemovedEvent;

class FLOW_DOCUMENT_API FlowDocument : public flow::document::Document
{
  Q_OBJECT

public:
  static std::unique_ptr<flow::document::Document> create();

public:
  ~FlowDocument() override;

  void addNode(flow::node::Node *node);
  void removeNode(flow::node::Node *node);

Q_SIGNALS:
  void event(const ObjectsChangedPropertiesEvent &event);
  void event(const ObjectsAddedEvent &event);
  void event(const ObjectsRemovedEvent &event);

protected:
  explicit FlowDocument(QObject *parent = nullptr);

private:
  QList<flow::node::Node *> m_nodes;
};

#endif//FLOW_FLOW_DOCUMENT_H
