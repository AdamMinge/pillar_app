#ifndef FLOW_FLOW_DOCUMENT_READER_H
#define FLOW_FLOW_DOCUMENT_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class FlowDocumentReader
{
  class FlowDocumentReaderImpl;

public:
  explicit FlowDocumentReader();
  ~FlowDocumentReader();

private:
  std::unique_ptr<FlowDocumentReaderImpl> m_impl;
};

#endif//FLOW_FLOW_DOCUMENT_READER_H
