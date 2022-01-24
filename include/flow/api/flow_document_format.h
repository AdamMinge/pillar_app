#ifndef FLOW_INTERFACE_FLOW_DOCUMENT_FORMAT_H
#define FLOW_INTERFACE_FLOW_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/api/document_format.h"
/* -------------------------------------------------------------------------- */

namespace api
{

  class IFlowDocumentFormat : public IDocumentFormat
  {
    Q_OBJECT

  public:
    explicit IFlowDocumentFormat(QObject *parent = nullptr);
    ~IFlowDocumentFormat() override;
  };

  class IReadableFlowDocumentFormat : public IFlowDocumentFormat
  {
    Q_OBJECT

  public:
    explicit IReadableFlowDocumentFormat(QObject *parent = nullptr);
    ~IReadableFlowDocumentFormat() override;

    bool save(const IDocument &document) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

  class IWritableFlowDocumentFormat : public IFlowDocumentFormat
  {
    Q_OBJECT

  public:
    explicit IWritableFlowDocumentFormat(QObject *parent = nullptr);
    ~IWritableFlowDocumentFormat() override;

    std::unique_ptr<IDocument> load(const QString &file_name) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

}// namespace api

#endif//FLOW_INTERFACE_FLOW_DOCUMENT_FORMAT_H
