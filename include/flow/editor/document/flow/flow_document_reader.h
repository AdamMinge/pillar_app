#ifndef FLOW_FLOW_DOCUMENT_READER_H
#define FLOW_FLOW_DOCUMENT_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

class FlowDocument;

class FlowDocumentReader
{
  class FlowDocumentReaderImpl;

public:
  explicit FlowDocumentReader();
  ~FlowDocumentReader();

  std::unique_ptr<FlowDocument> read(QIODevice &device,
                                     QString *error = nullptr);
  std::unique_ptr<FlowDocument> read(const QString &file_name,
                                     QString *error = nullptr);

  bool isValid(const QString &file_name);
  bool isValid(QIODevice &device);

private:
  std::unique_ptr<FlowDocumentReaderImpl> m_impl;
};

#endif//FLOW_FLOW_DOCUMENT_READER_H
