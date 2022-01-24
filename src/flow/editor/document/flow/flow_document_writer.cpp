/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamWriter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document_writer.h"
#include "flow/editor/document/flow/flow_document.h"
/* -------------------------------------------------------------------------- */

/* --------------------------- FlowDocumentWriterImpl ----------------------- */

class FlowDocumentWriter::FlowDocumentWriterImpl
{
public:
  explicit FlowDocumentWriterImpl() = default;
  ~FlowDocumentWriterImpl() = default;

  void writeDocument(const FlowDocument &document, QIODevice &device);

private:
  void writeDocument(QXmlStreamWriter &writer, const FlowDocument &document);
};

void FlowDocumentWriter::FlowDocumentWriterImpl::writeDocument(const FlowDocument &document, QIODevice &device)
{
  QXmlStreamWriter writer(&device);

  writer.writeStartDocument();
  writeDocument(writer, document);
  writer.writeEndDocument();
}

void FlowDocumentWriter::FlowDocumentWriterImpl::writeDocument(QXmlStreamWriter &writer, const FlowDocument &document)
{
  writer.writeStartElement(QStringLiteral("flow document"));

  writer.writeEndElement();
}

/* ------------------------------- FlowDocumentWriter ---------------------------- */

FlowDocumentWriter::FlowDocumentWriter()
    : m_impl(std::make_unique<FlowDocumentWriterImpl>())
{
}

FlowDocumentWriter::~FlowDocumentWriter() = default;


void FlowDocumentWriter::write(const FlowDocument &document, QIODevice &device)
{
  m_impl->writeDocument(document, device);
}

bool FlowDocumentWriter::write(const FlowDocument &document, const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;

  m_impl->writeDocument(document, file);

  if (file.error() != QFileDevice::NoError)
    return false;

  file.close();
  return true;
}
