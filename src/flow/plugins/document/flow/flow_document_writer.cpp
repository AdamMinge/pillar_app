/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_document_writer.h"
#include "flow/plugins/document/flow/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamWriter>
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

void FlowDocumentWriter::FlowDocumentWriterImpl::writeDocument(
  const FlowDocument &document, QIODevice &device)
{
  QXmlStreamWriter writer(&device);

  writer.writeStartDocument();
  writeDocument(writer, document);
  writer.writeEndDocument();
}

void FlowDocumentWriter::FlowDocumentWriterImpl::writeDocument(
  QXmlStreamWriter &writer, const FlowDocument &document)
{
  writer.writeStartElement(QStringLiteral("flow"));

  writer.writeEndElement();
}

/* ------------------------------- FlowDocumentWriter ---------------------------- */

FlowDocumentWriter::FlowDocumentWriter()
    : m_impl(std::make_unique<FlowDocumentWriterImpl>())
{}

FlowDocumentWriter::~FlowDocumentWriter() = default;


void FlowDocumentWriter::write(const FlowDocument &document, QIODevice &device)
{
  m_impl->writeDocument(document, device);
}

bool FlowDocumentWriter::write(
  const FlowDocument &document, const QString &file_name, QString *error)
{
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return false;
  }

  m_impl->writeDocument(document, file);

  if (file.error() != QFileDevice::NoError)
  {
    if (error) *error = file.errorString();
    return false;
  }

  file.close();
  return true;
}
