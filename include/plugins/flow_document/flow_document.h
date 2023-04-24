#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointer>
/* ----------------------------------- Flow --------------------------------- */
#include <flow/document/document.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;
class ChangeEvent;

class FLOW_DOCUMENT_API FlowDocument : public flow::Document {
  Q_OBJECT

 public:
  static std::unique_ptr<flow::Document> create();

 public:
  ~FlowDocument() override;

  void addNode(Node *node);
  void removeNode(Node *node);

 Q_SIGNALS:
  void event(const ChangeEvent &event);

 protected:
  explicit FlowDocument(QObject *parent = nullptr);

 private:
  QList<Node *> m_nodes;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_H
