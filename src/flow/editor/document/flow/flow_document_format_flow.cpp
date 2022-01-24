/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document_format_flow.h"
#include "flow/editor/document/flow/flow_document_reader.h"
#include "flow/editor/document/flow/flow_document_writer.h"
#include "flow/editor/document/flow/flow_document.h"
/* -------------------------------------------------------------------------- */

FlowDocumentFormatFlow::FlowDocumentFormatFlow(QObject *parent)
    : IFlowDocumentFormat(parent)
{
}

FlowDocumentFormatFlow::~FlowDocumentFormatFlow() = default;

QString FlowDocumentFormatFlow::getNameFilter() const
{
  return tr("Flow files (*.flow *.xml)");
}

QString FlowDocumentFormatFlow::getShortName() const
{
  return QStringLiteral("flow");
}

bool FlowDocumentFormatFlow::supportsFile(const QString &filename) const
{
  if (filename.endsWith(QLatin1String(".flow"), Qt::CaseSensitive))
    return true;

  if (filename.endsWith(QLatin1String(".xml"), Qt::CaseSensitive))
    return true;// TODO implementation ( check xml body )

  return false;
}

std::unique_ptr<api::IDocument> FlowDocumentFormatFlow::load(const QString &file_name)
{
  FlowDocumentReader document_reader;
  return document_reader.read(file_name);
}

bool FlowDocumentFormatFlow::save(const api::IDocument &document)
{
  FlowDocumentWriter document_writer;
  return document_writer.write(dynamic_cast< const FlowDocument&>(document), document.getFileName());
}