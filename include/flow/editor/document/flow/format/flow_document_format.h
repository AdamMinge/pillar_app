#ifndef FLOW_FLOW_DOCUMENT_FORMAT_H
#define FLOW_FLOW_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/format/document_format.h"
/* -------------------------------------------------------------------------- */

class FlowDocumentFormat : public DocumentFormat
{
  Q_OBJECT

public:
  explicit FlowDocumentFormat(QObject *parent = nullptr);
  ~FlowDocumentFormat() override;
};

class ReadableFlowDocumentFormat : public FlowDocumentFormat
{
  Q_OBJECT

public:
  explicit ReadableFlowDocumentFormat(QObject *parent = nullptr);
  ~ReadableFlowDocumentFormat() override;

  bool save(const Document &document) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableFlowDocumentFormat : public FlowDocumentFormat
{
  Q_OBJECT

public:
  explicit WritableFlowDocumentFormat(QObject *parent = nullptr);
  ~WritableFlowDocumentFormat() override;

  std::unique_ptr<Document> load(const QString &file_name) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

#endif//FLOW_FLOW_DOCUMENT_FORMAT_H
