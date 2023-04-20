#ifndef PLUGIN_FLOW_FLOW_STYLE_WRITER_H
#define PLUGIN_FLOW_FLOW_STYLE_WRITER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowStyle;

class FLOW_DOCUMENT_API FlowStyleWriter {
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

}  // namespace flow_document

#endif  // PLUGIN_FLOW_FLOW_STYLE_WRITER_H
