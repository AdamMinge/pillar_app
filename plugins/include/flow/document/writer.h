#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_WRITER_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;

class LIB_FLOW_DOCUMENT_API FlowDocumentWriter {
  class FlowDocumentWriterImpl;

 public:
  explicit FlowDocumentWriter();
  ~FlowDocumentWriter();

  void write(const FlowDocument &document, QIODevice &device);
  bool write(const FlowDocument &document, const QString &file_name,
             QString *error = nullptr);

 private:
  std::unique_ptr<FlowDocumentWriterImpl> m_impl;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_WRITER_H
