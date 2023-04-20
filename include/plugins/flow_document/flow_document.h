#ifndef FLOW_FLOW_DOCUMENT_H
#define FLOW_FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointer>
/* ----------------------------------- Flow --------------------------------- */
#include <flow/document/document.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;

class ObjectsChangedPropertiesEvent;
class ObjectsAddedEvent;
class ObjectsRemovedEvent;

class FLOW_DOCUMENT_API FlowDocument : public flow::Document {
  Q_OBJECT

 public:
  static std::unique_ptr<flow::Document> create();

 public:
  ~FlowDocument() override;

  void addNode(Node *node);
  void removeNode(Node *node);

 Q_SIGNALS:
  void event(const ObjectsChangedPropertiesEvent &event);
  void event(const ObjectsAddedEvent &event);
  void event(const ObjectsRemovedEvent &event);

 protected:
  explicit FlowDocument(QObject *parent = nullptr);

 private:
  QList<Node *> m_nodes;
};

}  // namespace flow_document

#endif  // FLOW_FLOW_DOCUMENT_H
