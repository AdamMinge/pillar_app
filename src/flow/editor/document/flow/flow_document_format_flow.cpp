/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_document_format_flow.h"
/* ------------------------------------ Api --------------------------------- */
#include "flow/api/document.h"
/* -------------------------------------------------------------------------- */

FlowDocumentFormatFlow::FlowDocumentFormatFlow(QObject *parent)
    : IFlowDocumentFormat(parent)
{
}

FlowDocumentFormatFlow::~FlowDocumentFormatFlow() = default;

QString FlowDocumentFormatFlow::getNameFilter() const
{
  return tr("Project files (*.flow *.xml)");
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
  return nullptr;// TODO implementation
}

bool FlowDocumentFormatFlow::save(const api::IDocument &document)
{
  return false;// TODO implementation
}