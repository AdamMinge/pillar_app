#ifndef PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H
#define PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/document_format.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowDocumentFormat
    : public flow::document::DocumentFormat
{
  Q_OBJECT
  Q_INTERFACES(flow::document::DocumentFormat)

public:
  explicit FlowDocumentFormat(QObject *parent = nullptr);
  ~FlowDocumentFormat() override;
};

Q_DECLARE_INTERFACE(FlowDocumentFormat, "org.flow.FlowDocumentFormat")

#endif//PLUGIN_FLOW_FLOW_DOCUMENT_FORMAT_H
