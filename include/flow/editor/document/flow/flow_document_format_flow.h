#ifndef FLOW_DOCUMENT_FORMAT_FLOW_H
#define FLOW_DOCUMENT_FORMAT_FLOW_H

/* ------------------------------------ Api --------------------------------- */
#include "flow/api/flow_document_format.h"
/* -------------------------------------------------------------------------- */

class FlowDocumentFormatFlow : public api::IFlowDocumentFormat
{
  Q_OBJECT

public:
  explicit FlowDocumentFormatFlow(QObject *parent = nullptr);
  ~FlowDocumentFormatFlow() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<api::IDocument> load(const QString &file_name) override;
  bool save(const api::IDocument &document) override;
};

#endif//FLOW_DOCUMENT_FORMAT_FLOW_H
