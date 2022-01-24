/* ------------------------------------ Qt ---------------------------------- */
#include <QXmlStreamWriter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document_writer.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- FlowDocumentWriterImpl -------------------------- */

class FlowDocumentWriter::FlowDocumentWriterImpl
{
public:
  explicit FlowDocumentWriterImpl() = default;
  ~FlowDocumentWriterImpl() = default;
};

/* ------------------------------- FlowDocumentWriter ---------------------------- */

FlowDocumentWriter::FlowDocumentWriter()
    : m_impl(std::make_unique<FlowDocumentWriterImpl>())
{
}

FlowDocumentWriter::~FlowDocumentWriter() = default;
