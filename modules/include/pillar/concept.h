#ifndef PILLAR_CONCEPT_H
#define PILLAR_CONCEPT_H

/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class Document;
class FileFormat;

template <typename TYPE>
concept IsDocument = std::derived_from<TYPE, Document>;

template <typename TYPE>
concept IsFileFormat = std::derived_from<TYPE, FileFormat>;

}  // namespace pillar

#endif  // PILLAR_CONCEPT_H
