#ifndef FLOW_DOCUMENT_CONCEPT_H
#define FLOW_DOCUMENT_CONCEPT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;
class Layer;
class Object;

template <typename TYPE>
concept IsNode = std::derived_from<TYPE, Node>;

template <typename TYPE>
concept IsLayer = std::derived_from<TYPE, Layer>;

template <typename TYPE>
concept IsObject = std::derived_from<TYPE, Object>;

template <typename TYPE>
concept IsWidget = std::derived_from<TYPE, QWidget>;

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONCEPT_H
