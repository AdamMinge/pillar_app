#ifndef PLUGIN_FLOW_DOCUMENT_FORMAT_FLOW_H
#define PLUGIN_FLOW_DOCUMENT_FORMAT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
#include "flow/plugins/flow_document/flow_document_format.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class FLOW_DOCUMENT_API FlowDocumentFormatFlow : public FlowDocumentFormat {
  Q_OBJECT
  Q_INTERFACES(plugin::flow_document::FlowDocumentFormat)

 public:
  explicit FlowDocumentFormatFlow(QObject *parent = nullptr);
  ~FlowDocumentFormatFlow() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<flow::Document> load(const QString &file_name,
                                       QString *error) override;
  bool save(const flow::Document &document, const QString &file_name,
            QString *error) override;
};

}  // namespace plugin::flow_document

#endif  // PLUGIN_FLOW_DOCUMENT_FORMAT_FLOW_H
