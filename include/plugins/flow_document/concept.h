#ifndef FLOW_DOCUMENT_CONCEPT_H
#define FLOW_DOCUMENT_CONCEPT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;
class Object;

template <typename TYPE>
concept IsNode = std::derived_from<TYPE, Node>;

template <typename TYPE>
concept IsObject = std::derived_from<TYPE, Object>;

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONCEPT_H
