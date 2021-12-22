/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document.h"
#include "flow/editor/document/flow/format/flow_document_format.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<FlowDocument> FlowDocument::create()
{
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(Type::Flow, parent)
{
}

FlowDocument::~FlowDocument() = default;
