#ifndef PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H
#define PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H

/* ----------------------------------- Flow --------------------------------- */
#include <flow/document/document_format.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API FlowDocumentFormat : public flow::DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(flow::DocumentFormat)

 public:
  explicit FlowDocumentFormat(QObject *parent = nullptr);
  ~FlowDocumentFormat() override;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::FlowDocumentFormat,
                    "org.flow.FlowDocumentFormat")

#endif  // PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H
