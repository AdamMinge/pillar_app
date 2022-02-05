#ifndef FLOW_DOCUMENT_FORMAT_FLOW_H
#define FLOW_DOCUMENT_FORMAT_FLOW_H

/* ------------------------------------ Api --------------------------------- */
#include "flow/api/document/flow_document_format.h"
/* -------------------------------------------------------------------------- */

class FlowDocumentFormatFlow : public api::document::IFlowDocumentFormat
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
