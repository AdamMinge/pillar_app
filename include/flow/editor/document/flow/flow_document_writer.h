#ifndef FLOW_FLOW_DOCUMENT_WRITER_H
#define FLOW_FLOW_DOCUMENT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class FlowDocument;

class FlowDocumentWriter
{
  class FlowDocumentWriterImpl;

public:
  explicit FlowDocumentWriter();
  ~FlowDocumentWriter();

  void write(const FlowDocument &document, QIODevice &device);
  bool write(const FlowDocument &document, const QString &file_name, QString *error = nullptr);

private:
  std::unique_ptr<FlowDocumentWriterImpl> m_impl;
};

#endif//FLOW_FLOW_DOCUMENT_WRITER_H
