#ifndef FLOW_FLOW_DOCUMENT_WRITER_H
#define FLOW_FLOW_DOCUMENT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class FlowDocumentWriter
{
  class FlowDocumentWriterImpl;

public:
  explicit FlowDocumentWriter();
  ~FlowDocumentWriter();

private:
  std::unique_ptr<FlowDocumentWriterImpl> m_impl;
};

#endif//FLOW_FLOW_DOCUMENT_WRITER_H
