#ifndef UTILS_SERIALIZER_SERIALIZABLE_H
#define UTILS_SERIALIZER_SERIALIZABLE_H

/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class OArchive;
class IArchive;

template <typename TYPE>
concept IsSerializable = requires(const TYPE &object, OArchive &s) {
  {
    std::invoke(&TYPE::serialize, std::declval<TYPE>(),
                std::declval<OArchive &>())
    } -> std::same_as<void>;
};

template <typename TYPE>
concept IsDeserializable = requires(TYPE &object, IArchive &s) {
  {
    std::invoke(&TYPE::deserialize, std::declval<TYPE>(),
                std::declval<IArchive &>())
    } -> std::same_as<void>;
};

class SERIALIZER_API Serializable {
 public:
  Serializable() = default;
  virtual ~Serializable() = default;

  virtual void serialize(OArchive &archive) const = 0;
  virtual void deserialize(IArchive &archive) = 0;
};

}  // namespace utils

#endif  // UTILS_SERIALIZER_SERIALIZABLE_H
