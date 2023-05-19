#ifndef UTILS_CONTAINER_HASH_H
#define UTILS_CONTAINER_HASH_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "utils/container/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

struct CONTAINER_API QtUuidHash {
  std::size_t operator()(const QUuid& uuid) const {
    return std::hash<std::string>()(uuid.toString().toStdString());
  }
};

}  // namespace utils

#endif  // UTILS_CONTAINER_HASH_H
