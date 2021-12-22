/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/format/flow_document_format.h"
#include "flow/editor/document/document.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------- FlowDocumentFormat --------------------------- */

FlowDocumentFormat::FlowDocumentFormat(QObject *parent)
    : DocumentFormat(parent)
{
}

FlowDocumentFormat::~FlowDocumentFormat() = default;

/* --------------------------- ReadableFlowDocumentFormat ----------------------- */

ReadableFlowDocumentFormat::ReadableFlowDocumentFormat(QObject *parent)
    : FlowDocumentFormat(parent)
{
}

ReadableFlowDocumentFormat::~ReadableFlowDocumentFormat() = default;

bool ReadableFlowDocumentFormat::save(const Document &document)
{
  return false;
}

ReadableFlowDocumentFormat::Capabilities ReadableFlowDocumentFormat::getCapabilities() const
{
  return Capability::Read;
}

/* --------------------------- WritableFlowDocumentFormat ----------------------- */

WritableFlowDocumentFormat::WritableFlowDocumentFormat(QObject *parent)
    : FlowDocumentFormat(parent)
{
}

WritableFlowDocumentFormat::~WritableFlowDocumentFormat() = default;

std::unique_ptr<Document> WritableFlowDocumentFormat::load(const QString &file_name)
{
  return nullptr;
}

WritableFlowDocumentFormat::Capabilities WritableFlowDocumentFormat::getCapabilities() const
{
  return Capability::Write;
}
