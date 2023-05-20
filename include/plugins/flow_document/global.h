#ifndef FLOW_DOCUMENT_GLOBAL_H
#define FLOW_DOCUMENT_GLOBAL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLatin1String>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace mimetype {

constexpr QLatin1String Layers = QLatin1String("application/vnd.layer.list");

}  // namespace mimetype

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_GLOBAL_H
