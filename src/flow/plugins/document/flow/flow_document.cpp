/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_document.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::document::Document> FlowDocument::create()
{
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent)
{}

FlowDocument::~FlowDocument() = default;
