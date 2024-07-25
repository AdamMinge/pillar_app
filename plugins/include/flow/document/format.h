#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_FORMAT_FLOW_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_FORMAT_FLOW_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/document/document_format.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API FlowDocumentFormat : public pillar::DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::DocumentFormat)

 public:
  explicit FlowDocumentFormat(QObject *parent = nullptr);
  ~FlowDocumentFormat() override;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::FlowDocumentFormat, "org.flow.FlowDocumentFormat")

namespace flow {

class LIB_FLOW_DOCUMENT_API FlowDocumentFormatFlow : public FlowDocumentFormat {
  Q_OBJECT
  Q_INTERFACES(flow::FlowDocumentFormat)

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

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_FORMAT_FLOW_H
