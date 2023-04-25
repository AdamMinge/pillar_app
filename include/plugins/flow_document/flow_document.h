#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointer>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/document/document.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ChangeEvent;
class Graph;

class FLOW_DOCUMENT_API FlowDocument : public egnite::Document {
  Q_OBJECT

 public:
  static std::unique_ptr<egnite::Document> create();

 public:
  ~FlowDocument() override;

  [[nodiscard]] const Graph *getGraph() const;
  [[nodiscard]] Graph *getGraph();

 Q_SIGNALS:
  void event(const ChangeEvent &event);

 protected:
  explicit FlowDocument(QObject *parent = nullptr);

 private:
  Graph *m_graph;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_H
