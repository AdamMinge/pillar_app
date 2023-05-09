#ifndef UTILS_VIEW_CONCEPT_H
#define UTILS_VIEW_CONCEPT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
/* ----------------------------------- Local -------------------------------- */
#include "utils/view/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

template <typename TYPE>
concept IsView = std::derived_from<TYPE, QAbstractItemView>;

}

#endif  // UTILS_VIEW_CONCEPT_H