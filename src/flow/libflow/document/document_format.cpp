/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/document/document_format.h"
#include "flow/libflow/document/document.h"
/* -------------------------------------------------------------------------- */

namespace flow::document
{

  /* ----------------------------- DocumentFormat --------------------------- */

  DocumentFormat::DocumentFormat(QObject *parent) : FileFormat(parent) {}

  DocumentFormat::~DocumentFormat() = default;

  /* -------------------------- ReadableDocumentFormat ---------------------- */

  ReadableDocumentFormat::ReadableDocumentFormat(QObject *parent)
      : DocumentFormat(parent)
  {}

  ReadableDocumentFormat::~ReadableDocumentFormat() = default;

  bool ReadableDocumentFormat::save(
    const Document &document, const QString &file_name, QString *error)
  {
    if (error) *error = tr("Document format is readable only");

    return false;
  }

  ReadableDocumentFormat::Capabilities
  ReadableDocumentFormat::getCapabilities() const
  {
    return Capability::Read;
  }

  /* -------------------------- WritableDocumentFormat ---------------------- */

  WritableDocumentFormat::WritableDocumentFormat(QObject *parent)
      : DocumentFormat(parent)
  {}

  WritableDocumentFormat::~WritableDocumentFormat() = default;

  std::unique_ptr<Document>
  WritableDocumentFormat::load(const QString &file_name, QString *error)
  {
    if (error) *error = tr("Document format is writable only");

    return nullptr;
  }

  WritableDocumentFormat::Capabilities
  WritableDocumentFormat::getCapabilities() const
  {
    return Capability::Write;
  }

}// namespace flow::document
