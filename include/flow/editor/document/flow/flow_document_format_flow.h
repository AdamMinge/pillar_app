#ifndef FLOW_DOCUMENT_FORMAT_FLOW_H
#define FLOW_DOCUMENT_FORMAT_FLOW_H

/* ------------------------------------ Local ------------------------------- */
#include "flow/editor/document/flow/flow_document_format.h"
/* -------------------------------------------------------------------------- */

class FlowDocumentFormatFlow : public FlowDocumentFormat
{
  Q_OBJECT

public:
  explicit FlowDocumentFormatFlow(QObject *parent = nullptr);
  ~FlowDocumentFormatFlow() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<api::document::IDocument> load(const QString &file_name,
                                                 QString *error) override;
  bool save(const api::document::IDocument &document, const QString &file_name,
            QString *error) override;
};

#endif//FLOW_DOCUMENT_FORMAT_FLOW_H
