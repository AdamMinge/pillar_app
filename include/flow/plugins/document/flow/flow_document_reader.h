#ifndef PLUGIN_FLOW_FLOW_DOCUMENT_READER_H
#define PLUGIN_FLOW_FLOW_DOCUMENT_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowDocument;

class FLOW_DOCUMENT_API FlowDocumentReader
{
  class FlowDocumentReaderImpl;

public:
  explicit FlowDocumentReader();
  ~FlowDocumentReader();

  std::unique_ptr<FlowDocument>
  read(QIODevice &device, QString *error = nullptr);
  std::unique_ptr<FlowDocument>
  read(const QString &file_name, QString *error = nullptr);

  bool isValid(const QString &file_name);
  bool isValid(QIODevice &device);

private:
  std::unique_ptr<FlowDocumentReaderImpl> m_impl;
};

#endif//PLUGIN_FLOW_FLOW_DOCUMENT_READER_H
