#ifndef UTILS_POINTER_CAST_UNIQUE_PTR_CAST_H
#define UTILS_POINTER_CAST_UNIQUE_PTR_CAST_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "utils/pointer_cast/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

template <typename TO, typename FROM>
std::unique_ptr<TO> POINTER_CAST_API
cast_unique_ptr(std::unique_ptr<FROM> &&from) {
  return std::unique_ptr<TO>(dynamic_cast<TO *>(from.release()));
}

}  // namespace utils

#endif  // UTILS_POINTER_CAST_UNIQUE_PTR_CAST_H
