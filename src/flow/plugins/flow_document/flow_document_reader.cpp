/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/flow_document_reader.h"

#include "flow/plugins/flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamReader>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/pointer_cast/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

/* --------------------------- FlowDocumentReaderImpl ----------------------- */

class FlowDocumentReader::FlowDocumentReaderImpl {
 public:
  explicit FlowDocumentReaderImpl() = default;
  ~FlowDocumentReaderImpl() = default;

  std::unique_ptr<FlowDocument> readDocument(QIODevice &device);
  bool isValid(QIODevice &device);

 private:
  std::unique_ptr<FlowDocument> readDocument(QXmlStreamReader &reader);
};

std::unique_ptr<FlowDocument>
FlowDocumentReader::FlowDocumentReaderImpl::readDocument(QIODevice &device) {
  QXmlStreamReader reader;
  reader.setDevice(&device);

  if (reader.readNextStartElement() && reader.name() != QStringLiteral("flow"))
    return nullptr;

  return readDocument(reader);
}

std::unique_ptr<FlowDocument>
FlowDocumentReader::FlowDocumentReaderImpl::readDocument(
    QXmlStreamReader &reader) {
  return utils::cast_unique_ptr<FlowDocument>(FlowDocument::create());
}

bool FlowDocumentReader::FlowDocumentReaderImpl::isValid(QIODevice &device) {
  QXmlStreamReader reader;
  reader.setDevice(&device);

  if (reader.readNextStartElement() &&
      reader.name() != QStringLiteral("flow document"))
    return false;

  return true;
}

/* ----------------------------- FlowDocumentReader ------------------------- */

FlowDocumentReader::FlowDocumentReader()
    : m_impl(std::make_unique<FlowDocumentReaderImpl>()) {}

FlowDocumentReader::~FlowDocumentReader() = default;

std::unique_ptr<FlowDocument> FlowDocumentReader::read(QIODevice &device,
                                                       QString *error) {
  auto document = m_impl->readDocument(device);
  if (!document && error) *error = QObject::tr("Failed to load document");
  return document;
}

std::unique_ptr<FlowDocument> FlowDocumentReader::read(const QString &file_name,
                                                       QString *error) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return nullptr;
  }

  auto document = m_impl->readDocument(file);
  if (!document && error) *error = QObject::tr("Failed to load document");

  return document;
}

bool FlowDocumentReader::isValid(const QString &file_name) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

  return m_impl->isValid(file);
}

bool FlowDocumentReader::isValid(QIODevice &device) {
  return m_impl->isValid(device);
}

}  // namespace plugin::flow_document