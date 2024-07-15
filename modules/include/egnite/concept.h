#ifndef EGNITE_CONCEPT_H
#define EGNITE_CONCEPT_H

/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class Document;
class FileFormat;

template <typename TYPE>
concept IsDocument = std::derived_from<TYPE, Document>;

template <typename TYPE>
concept IsFileFormat = std::derived_from<TYPE, FileFormat>;

}  // namespace egnite

#endif  // EGNITE_CONCEPT_H
