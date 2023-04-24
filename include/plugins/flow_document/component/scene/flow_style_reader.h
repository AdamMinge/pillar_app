#ifndef FLOW_DOCUMENT_FLOW_STYLE_READER_H
#define FLOW_DOCUMENT_FLOW_STYLE_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowStyle;

class FLOW_DOCUMENT_API FlowStyleReader {
  class FlowStyleReaderImpl;

 public:
  explicit FlowStyleReader();
  ~FlowStyleReader();

  std::unique_ptr<FlowStyle> read(QIODevice &device, QString *error = nullptr);
  std::unique_ptr<FlowStyle> read(const QString &file_name,
                                  QString *error = nullptr);

 private:
  std::unique_ptr<FlowStyleReaderImpl> m_impl;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_STYLE_READER_H
