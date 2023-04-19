/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/flow_document_format.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

FlowDocumentFormat::FlowDocumentFormat(QObject *parent)
    : DocumentFormat(parent) {}

FlowDocumentFormat::~FlowDocumentFormat() = default;

}  // namespace plugin::flow_document