#ifndef PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H
#define PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/document_format.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class FLOW_DOCUMENT_API FlowDocumentFormat : public flow::DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(flow::DocumentFormat)

 public:
  explicit FlowDocumentFormat(QObject *parent = nullptr);
  ~FlowDocumentFormat() override;
};

}  // namespace plugin::flow_document

Q_DECLARE_INTERFACE(plugin::flow_document::FlowDocumentFormat,
                    "org.flow.FlowDocumentFormat")

#endif  // PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H
