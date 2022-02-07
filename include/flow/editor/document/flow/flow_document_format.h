#ifndef FLOW_FLOW_DOCUMENT_FORMAT_H
#define FLOW_FLOW_DOCUMENT_FORMAT_H

/* ------------------------------------ Api --------------------------------- */
#include <flow/api/document/document_format.h>
/* -------------------------------------------------------------------------- */

class FlowDocumentFormat : public api::document::IDocumentFormat
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

  bool save(const api::document::IDocument &document, const QString &file_name,
            QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableFlowDocumentFormat : public FlowDocumentFormat
{
  Q_OBJECT

public:
  explicit WritableFlowDocumentFormat(QObject *parent = nullptr);
  ~WritableFlowDocumentFormat() override;

  std::unique_ptr<api::document::IDocument> load(const QString &file_name,
                                                 QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

#endif//FLOW_FLOW_DOCUMENT_FORMAT_H
