/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_format.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowDocumentFormat::FlowDocumentFormat(QObject *parent)
    : DocumentFormat(parent) {}

FlowDocumentFormat::~FlowDocumentFormat() = default;

}  // namespace flow_document