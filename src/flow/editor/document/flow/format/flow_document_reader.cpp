/* ------------------------------------ Qt ---------------------------------- */
#include <QXmlStreamReader>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/format/flow_document_reader.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- FlowDocumentReaderImpl -------------------------- */

class FlowDocumentReader::FlowDocumentReaderImpl
{
public:
  explicit FlowDocumentReaderImpl() = default;
  ~FlowDocumentReaderImpl() = default;
};

/* ------------------------------- FlowDocumentReader ---------------------------- */

FlowDocumentReader::FlowDocumentReader()
    : m_impl(std::make_unique<FlowDocumentReaderImpl>())
{
}

FlowDocumentReader::~FlowDocumentReader() = default;
