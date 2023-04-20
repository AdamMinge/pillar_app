/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_format.h"
/* ----------------------------------- Flow --------------------------------- */
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowDocumentFormat::FlowDocumentFormat(QObject *parent)
    : DocumentFormat(parent) {}

FlowDocumentFormat::~FlowDocumentFormat() = default;

}  // namespace flow_document