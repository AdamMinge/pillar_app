#ifndef FLOW_DOCUMENT_FLOW_STYLE_WRITER_H
#define FLOW_DOCUMENT_FLOW_STYLE_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowStyle;

class LIB_FLOW_DOCUMENT_API FlowStyleWriter {
  class FlowStyleWriterImpl;

 public:
  explicit FlowStyleWriter();
  ~FlowStyleWriter();

  void write(const FlowStyle &style, QIODevice &device);
  bool write(const FlowStyle &style, const QString &file_name,
             QString *error = nullptr);

 private:
  std::unique_ptr<FlowStyleWriterImpl> m_impl;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_STYLE_WRITER_H
