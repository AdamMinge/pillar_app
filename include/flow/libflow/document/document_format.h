#ifndef FLOW_INTERFACE_DOCUMENT_FORMAT_H
#define FLOW_INTERFACE_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/file_format.h"
/* -------------------------------------------------------------------------- */

namespace flow::document
{

  class Document;

  class LIB_FLOW_API DocumentFormat : public FileFormat
  {
    Q_OBJECT

  public:
    explicit DocumentFormat(QObject *parent = nullptr);
    ~DocumentFormat() override;

    virtual std::unique_ptr<Document>
    load(const QString &file_name, QString *error) = 0;
    virtual bool save(
      const Document &document, const QString &file_name, QString *error) = 0;

    [[nodiscard]] virtual QString getDocumentId() const = 0;
  };

}// namespace flow::document

#endif//FLOW_INTERFACE_DOCUMENT_FORMAT_H
