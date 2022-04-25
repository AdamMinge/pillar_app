#ifndef PLUGIN_FLOW_DOCUMENT_FORMAT_FLOW_H
#define PLUGIN_FLOW_DOCUMENT_FORMAT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
#include "flow/plugins/document/flow/flow_document_format.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowDocumentFormatFlow : public FlowDocumentFormat
{
  Q_OBJECT
  Q_INTERFACES(FlowDocumentFormat)

public:
  explicit FlowDocumentFormatFlow(QObject *parent = nullptr);
  ~FlowDocumentFormatFlow() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<flow::document::Document>
  load(const QString &file_name, QString *error) override;
  bool save(
    const flow::document::Document &document, const QString &file_name,
    QString *error) override;
};

#endif//PLUGIN_FLOW_DOCUMENT_FORMAT_FLOW_H
