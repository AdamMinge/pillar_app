/* ----------------------------------- Local -------------------------------- */
#include "flow/document/writer.h"

#include "flow/document/document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/json_archive.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------- FlowDocumentWriterImpl ----------------------- */

class FlowDocumentWriter::FlowDocumentWriterImpl {
 public:
  explicit FlowDocumentWriterImpl() = default;
  ~FlowDocumentWriterImpl() = default;

  void writeDocument(const FlowDocument &document, QIODevice &device);
};

void FlowDocumentWriter::FlowDocumentWriterImpl::writeDocument(
    const FlowDocument &document, QIODevice &device) {
  qtils::OJsonArchive archive(device);
  archive << qtils::ArchiveProperty("flow_document", document);
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

}  // namespace flow