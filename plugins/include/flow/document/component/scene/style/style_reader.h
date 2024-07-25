#ifndef FLOW_DOCUMENT_FLOW_STYLE_READER_H
#define FLOW_DOCUMENT_FLOW_STYLE_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowStyle;

class LIB_FLOW_DOCUMENT_API FlowStyleReader {
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

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_STYLE_READER_H
