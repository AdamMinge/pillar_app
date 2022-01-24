/* ----------------------------------- Local -------------------------------- */
#include "flow/api/flow_document_format.h"
#include "flow/api/document.h"
/* -------------------------------------------------------------------------- */

namespace api
{

  /* ------------------------------- FlowDocumentFormat --------------------------- */

  IFlowDocumentFormat::IFlowDocumentFormat(QObject *parent)
      : IDocumentFormat(parent)
  {
  }

  IFlowDocumentFormat::~IFlowDocumentFormat() = default;

  /* --------------------------- ReadableFlowDocumentFormat ----------------------- */

  IReadableFlowDocumentFormat::IReadableFlowDocumentFormat(QObject *parent)
      : IFlowDocumentFormat(parent)
  {
  }

  IReadableFlowDocumentFormat::~IReadableFlowDocumentFormat() = default;

  bool IReadableFlowDocumentFormat::save(const IDocument &document)
  {
    return false;
  }

  IReadableFlowDocumentFormat::Capabilities IReadableFlowDocumentFormat::getCapabilities() const
  {
    return Capability::Read;
  }

  /* --------------------------- WritableFlowDocumentFormat ----------------------- */

  IWritableFlowDocumentFormat::IWritableFlowDocumentFormat(QObject *parent)
      : IFlowDocumentFormat(parent)
  {
  }

  IWritableFlowDocumentFormat::~IWritableFlowDocumentFormat() = default;

  std::unique_ptr<IDocument> IWritableFlowDocumentFormat::load(const QString &file_name)
  {
    return nullptr;
  }

  IWritableFlowDocumentFormat::Capabilities IWritableFlowDocumentFormat::getCapabilities() const
  {
    return Capability::Write;
  }

}//namespace api