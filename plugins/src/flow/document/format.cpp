/* ----------------------------------- Local -------------------------------- */
#include "flow/document/format.h"

#include "flow/document/document.h"
#include "flow/document/reader.h"
#include "flow/document/writer.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------------- FlowDocumentFormat ------------------------- */

FlowDocumentFormat::FlowDocumentFormat(QObject *parent)
    : DocumentFormat(parent) {}

FlowDocumentFormat::~FlowDocumentFormat() = default;

/* --------------------------- FlowDocumentFormatFlow ----------------------- */

FlowDocumentFormatFlow::FlowDocumentFormatFlow(QObject *parent)
    : FlowDocumentFormat(parent) {}

FlowDocumentFormatFlow::~FlowDocumentFormatFlow() = default;

QString FlowDocumentFormatFlow::getNameFilter() const {
  return tr("Flow files (*.flow *.json)");
}

QString FlowDocumentFormatFlow::getShortName() const {
  return QStringLiteral("flow");
}

bool FlowDocumentFormatFlow::supportsFile(const QString &filename) const {
  if (filename.endsWith(QLatin1String(".flow"), Qt::CaseSensitive)) return true;

  if (filename.endsWith(QLatin1String(".json"), Qt::CaseSensitive)) {
    FlowDocumentReader document_reader;
    return document_reader.isValid(filename);
  }

  return false;
}

std::unique_ptr<pillar::Document> FlowDocumentFormatFlow::load(
    const QString &file_name, QString *error) {
  FlowDocumentReader document_reader;
  return document_reader.read(file_name, error);
}

bool FlowDocumentFormatFlow::save(const pillar::Document &document,
                                  const QString &file_name, QString *error) {
  FlowDocumentWriter document_writer;
  return document_writer.write(dynamic_cast<const FlowDocument &>(document),
                               file_name, error);
}

}  // namespace flow