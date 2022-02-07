/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document_format.h"
/* ------------------------------------ Api --------------------------------- */
#include "flow/api/document/document.h"
/* -------------------------------------------------------------------------- */


/* ----------------------------- FlowDocumentFormat ------------------------- */

FlowDocumentFormat::FlowDocumentFormat(QObject *parent)
    : IDocumentFormat(parent)
{}

FlowDocumentFormat::~FlowDocumentFormat() = default;

/* ------------------------- ReadableFlowDocumentFormat --------------------- */

ReadableFlowDocumentFormat::ReadableFlowDocumentFormat(QObject *parent)
    : FlowDocumentFormat(parent)
{}

ReadableFlowDocumentFormat::~ReadableFlowDocumentFormat() = default;

bool ReadableFlowDocumentFormat::save(const api::document::IDocument &document,
                                      const QString &file_name, QString *error)
{
  if (error) *error = tr("Document format is readable only");

  return false;
}

ReadableFlowDocumentFormat::Capabilities
ReadableFlowDocumentFormat::getCapabilities() const
{
  return Capability::Read;
}

/* ------------------------- WritableFlowDocumentFormat --------------------- */

WritableFlowDocumentFormat::WritableFlowDocumentFormat(QObject *parent)
    : FlowDocumentFormat(parent)
{}

WritableFlowDocumentFormat::~WritableFlowDocumentFormat() = default;

std::unique_ptr<api::document::IDocument>
WritableFlowDocumentFormat::load(const QString &file_name, QString *error)
{
  if (error) *error = tr("Document format is writable only");

  return nullptr;
}

WritableFlowDocumentFormat::Capabilities
WritableFlowDocumentFormat::getCapabilities() const
{
  return Capability::Write;
}
