#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_FORMAT_FLOW_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_FORMAT_FLOW_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow_document_format.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API FlowDocumentFormatFlow : public FlowDocumentFormat {
  Q_OBJECT
  Q_INTERFACES(flow_document::FlowDocumentFormat)

 public:
  explicit FlowDocumentFormatFlow(QObject *parent = nullptr);
  ~FlowDocumentFormatFlow() override;

  [[nodiscard]] QString getNameFilter() const override;
  [[nodiscard]] QString getShortName() const override;
  [[nodiscard]] bool supportsFile(const QString &filename) const override;

  std::unique_ptr<pillar::Document> load(const QString &file_name,
                                         QString *error) override;
  bool save(const pillar::Document &document, const QString &file_name,
            QString *error) override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_FORMAT_FLOW_H
