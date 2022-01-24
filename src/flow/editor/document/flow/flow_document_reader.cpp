/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamReader>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document.h"
#include "flow/editor/document/flow/flow_document_reader.h"
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/pointer_cast/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

/* --------------------------- FlowDocumentReaderImpl ----------------------- */

class FlowDocumentReader::FlowDocumentReaderImpl
{
public:
  explicit FlowDocumentReaderImpl() = default;
  ~FlowDocumentReaderImpl() = default;

  std::unique_ptr<FlowDocument> readDocument(QIODevice &device);

private:
  std::unique_ptr<FlowDocument> readDocument(QXmlStreamReader &writer);
};

std::unique_ptr<FlowDocument> FlowDocumentReader::FlowDocumentReaderImpl::readDocument(QIODevice &device)
{
  QXmlStreamReader reader;
  reader.setDevice(&device);

  if (!(reader.readNextStartElement() && reader.name() == QStringLiteral("document")))
    return nullptr;

  return readDocument(reader);
}

std::unique_ptr<FlowDocument> FlowDocumentReader::FlowDocumentReaderImpl::readDocument(QXmlStreamReader &writer)
{
  return utils::cast_unique_ptr<FlowDocument>(FlowDocument::create());
}

/* ------------------------------- FlowDocumentReader ---------------------------- */

FlowDocumentReader::FlowDocumentReader()
    : m_impl(std::make_unique<FlowDocumentReaderImpl>())
{
}

FlowDocumentReader::~FlowDocumentReader() = default;

std::unique_ptr<FlowDocument> FlowDocumentReader::read(QIODevice &device)
{
  return m_impl->readDocument(device);
}

std::unique_ptr<FlowDocument> FlowDocumentReader::read(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return nullptr;

  return m_impl->readDocument(file);
}