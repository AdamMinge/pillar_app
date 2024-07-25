/* ----------------------------------- Local -------------------------------- */
#include "flow/document/reader.h"

#include "flow/document/document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamReader>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/pointer/unique_ptr_cast.h>
#include <qtils/serializer/json_archive.h>
/* -------------------------------------------------------------------------- */

namespace flow {

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
  auto document = qtils::cast_unique_ptr<FlowDocument>(FlowDocument::create());

  qtils::IJsonArchive archive(device);
  archive >> qtils::ArchiveProperty("flow_document", document);

  return document;
}

bool FlowDocumentReader::FlowDocumentReaderImpl::isValid(QIODevice &device) {
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

}  // namespace flow