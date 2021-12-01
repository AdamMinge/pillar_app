/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/flow_document.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<FlowDocument> FlowDocument::create()
{
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject* parent) :
  Document(Type::Flow, parent)
{

}

FlowDocument::~FlowDocument() = default;
