/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

std::unique_ptr<egnite::Document> FlowDocument::create() {
  auto document = std::unique_ptr<FlowDocument>(new FlowDocument());
  return document;
}

FlowDocument::FlowDocument(QObject *parent)
    : Document(QLatin1String("FlowDocument"), parent) {}

FlowDocument::~FlowDocument() = default;
}  // namespace flow_document