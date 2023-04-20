#ifndef PLUGIN_FLOW_FLOW_DOCUMENT_WRITER_H
#define PLUGIN_FLOW_FLOW_DOCUMENT_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;

class FLOW_DOCUMENT_API FlowDocumentWriter {
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

}  // namespace flow_document

#endif  // PLUGIN_FLOW_FLOW_DOCUMENT_WRITER_H
