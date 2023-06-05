#ifndef UTILS_CONTAINER_MAP_H
#define UTILS_CONTAINER_MAP_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ------------------------------------- Qt --------------------------------- */
#include <QMap>
/* ----------------------------------- Local -------------------------------- */
#include "utils/container/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

template <typename VALUE, typename KEYS>
QMap<typename std::decay_t<KEYS>::value_type, VALUE> mapFromKeys(KEYS&& keys,
                                                                 VALUE value) {
  auto map = QMap<typename std::decay_t<KEYS>::value_type, VALUE>{};
  for (auto&& key : std::forward<KEYS>(keys)) {
    map[key] = value;
  }

  return map;
}

}  // namespace utils

#endif  // UTILS_CONTAINER_MAP_H
