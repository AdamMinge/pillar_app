#ifndef FLOW_FLOW_DOCUMENT_H
#define FLOW_FLOW_DOCUMENT_H

/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/document/document.h"
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}

class FLOW_DOCUMENT_API FlowDocument : public flow::document::Document
{
  Q_OBJECT

public:
  static std::unique_ptr<flow::document::Document> create();

public:
  ~FlowDocument() override;

protected:
  explicit FlowDocument(QObject *parent = nullptr);
};

#endif//FLOW_FLOW_DOCUMENT_H
