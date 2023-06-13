/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_reader.h"

#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamReader>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/pointer_cast/unique_ptr_cast.h>
#include <utils/serializer/xml_archive.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- FlowDocumentReaderImpl ----------------------- */

class FlowDocumentReader::FlowDocumentReaderImpl {
 public:
  explicit FlowDocumentReaderImpl() = default;
  ~FlowDocumentReaderImpl() = default;

  std::unique_ptr<FlowDocument> readDocument(QIODevice &device);
  bool isValid(QIODevice &device);
};

std::unique_ptr<FlowDocument>
FlowDocumentReader::FlowDocumentReaderImpl::readDocument(QIODevice &device) {
  auto document = utils::cast_unique_ptr<FlowDocument>(FlowDocument::create());

  utils::IXmlArchive archive(device);
  archive >> utils::ArchiveProperty("flow_document", document);

  return document;
}

bool FlowDocumentReader::FlowDocumentReaderImpl::isValid(QIODevice &device) {
  // QXmlStreamReader reader;
  // reader.setDevice(&device);

  // if (reader.readNextStartElement() &&
  //     reader.name() != QStringLiteral("flow document"))
  //   return false;

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

  return true;
  // return m_impl->isValid(file);
}

bool FlowDocumentReader::isValid(QIODevice &device) {
  return true;
  // return m_impl->isValid(device);
}

}  // namespace flow_document