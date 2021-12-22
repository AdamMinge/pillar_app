#ifndef FLOW_DOCUMENT_FORMAT_H
#define FLOW_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/file_format.h"
/* -------------------------------------------------------------------------- */

class Document;

class DocumentFormat : public FileFormat
{
  Q_OBJECT

public:
  using FileFormat::FileFormat;

  virtual std::unique_ptr<Document> load(const QString &file_name) = 0;
  virtual bool save(const Document &document) = 0;
};

#endif//FLOW_DOCUMENT_FORMAT_H
