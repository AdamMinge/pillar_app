#ifndef UTILS_SERIALIZER_SERIALIZABLE_H
#define UTILS_SERIALIZER_SERIALIZABLE_H

/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class OArchive;
class IArchive;

class SERIALIZER_API Serializable {
 public:
  Serializable() = default;
  virtual ~Serializable() = default;

  virtual void serialize(OArchive &archive) const = 0;
  virtual void deserialize(IArchive &archive) = 0;
};

}  // namespace utils

#endif  // UTILS_SERIALIZER_SERIALIZABLE_H
