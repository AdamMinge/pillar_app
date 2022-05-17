#ifndef PLUGIN_FLOW_FLOW_STYLE_READER_H
#define PLUGIN_FLOW_FLOW_STYLE_READER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowStyle;

class FLOW_DOCUMENT_API FlowStyleReader
{
  class FlowStyleReaderImpl;

public:
  explicit FlowStyleReader();
  ~FlowStyleReader();

  std::unique_ptr<FlowStyle> read(QIODevice &device, QString *error = nullptr);
  std::unique_ptr<FlowStyle>
  read(const QString &file_name, QString *error = nullptr);

private:
  std::unique_ptr<FlowStyleReaderImpl> m_impl;
};

#endif//PLUGIN_FLOW_FLOW_STYLE_READER_H
