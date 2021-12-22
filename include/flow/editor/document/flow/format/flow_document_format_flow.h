#ifndef FLOW_DOCUMENT_FORMAT_FLOW_H
#define FLOW_DOCUMENT_FORMAT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/format/flow_document_format.h"
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

  std::unique_ptr<Document> load(const QString &file_name) override;
  bool save(const Document &document) override;
};

#endif//FLOW_DOCUMENT_FORMAT_FLOW_H
