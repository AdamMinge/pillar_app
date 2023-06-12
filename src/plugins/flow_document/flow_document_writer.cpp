/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_writer.h"

#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/xml_archive.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- FlowDocumentWriterImpl ----------------------- */

class FlowDocumentWriter::FlowDocumentWriterImpl {
 public:
  explicit FlowDocumentWriterImpl() = default;
  ~FlowDocumentWriterImpl() = default;

  void writeDocument(const FlowDocument &document, QIODevice &device);
};

void FlowDocumentWriter::FlowDocumentWriterImpl::writeDocument(
    const FlowDocument &document, QIODevice &device) {
  utils::OXmlArchive archive(device);
  archive << utils::ArchiveProperty("flow_document", document);
}

/* ----------------------------- FlowDocumentWriter ------------------------- */

FlowDocumentWriter::FlowDocumentWriter()
    : m_impl(std::make_unique<FlowDocumentWriterImpl>()) {}

FlowDocumentWriter::~FlowDocumentWriter() = default;

void FlowDocumentWriter::write(const FlowDocument &document,
                               QIODevice &device) {
  m_impl->writeDocument(document, device);
}

bool FlowDocumentWriter::write(const FlowDocument &document,
                               const QString &file_name, QString *error) {
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return false;
  }

  m_impl->writeDocument(document, file);

  if (file.error() != QFileDevice::NoError) {
    if (error) *error = file.errorString();
    return false;
  }

  file.close();
  return true;
}

}  // namespace flow_document