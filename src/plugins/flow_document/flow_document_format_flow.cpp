/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_format_flow.h"

#include "flow_document/flow_document.h"
#include "flow_document/flow_document_reader.h"
#include "flow_document/flow_document_writer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowDocumentFormatFlow::FlowDocumentFormatFlow(QObject *parent)
    : FlowDocumentFormat(parent) {}

FlowDocumentFormatFlow::~FlowDocumentFormatFlow() = default;

QString FlowDocumentFormatFlow::getNameFilter() const {
  return tr("Flow files (*.flow *.xml)");
}

QString FlowDocumentFormatFlow::getShortName() const {
  return QStringLiteral("flow");
}

bool FlowDocumentFormatFlow::supportsFile(const QString &filename) const {
  if (filename.endsWith(QLatin1String(".flow"), Qt::CaseSensitive)) return true;

  if (filename.endsWith(QLatin1String(".xml"), Qt::CaseSensitive)) {
    FlowDocumentReader document_reader;
    return document_reader.isValid(filename);
  }

  return false;
}

std::unique_ptr<flow::Document> FlowDocumentFormatFlow::load(
    const QString &file_name, QString *error) {
  FlowDocumentReader document_reader;
  return document_reader.read(file_name, error);
}

bool FlowDocumentFormatFlow::save(const flow::Document &document,
                                  const QString &file_name, QString *error) {
  FlowDocumentWriter document_writer;
  return document_writer.write(dynamic_cast<const FlowDocument &>(document),
                               file_name, error);
}

}  // namespace flow_document