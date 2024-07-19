#ifndef AEGIS_RESULT_H
#define AEGIS_RESULT_H

/* --------------------------------- Standard ------------------------------- */
#include <variant>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/archive.h>
#include <qtils/serializer/serializable.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

template <typename T, typename E>
class Result : public qtils::Serializable {
 public:
  Result(T value);
  Result(E error);

  [[nodiscard]] bool hasValue() const;
  [[nodiscard]] bool hasError() const;

  [[nodiscard]] T value() const;
  [[nodiscard]] E error() const;

  void serialize(qtils::OArchive &archive) const override;

 private:
  std::variant<T, E> m_result;
};

template <typename T, typename E>
Result<T, E>::Result(T value) : m_result(std::move(value)) {}

template <typename T, typename E>
Result<T, E>::Result(E error) : m_result(std::move(error)) {}

template <typename T, typename E>
bool Result<T, E>::hasValue() const {
  return std::holds_alternative<T>(m_result);
}

template <typename T, typename E>
bool Result<T, E>::hasError() const {
  return std::holds_alternative<E>(m_result);
}

template <typename T, typename E>
T Result<T, E>::value() const {
  if (hasValue()) {
    return std::get<T>(m_result);
  } else {
    throw std::runtime_error("Tried to get value from an error result");
  }
}

template <typename T, typename E>
E Result<T, E>::error() const {
  if (hasError()) {
    return std::get<E>(m_result);
  } else {
    throw std::runtime_error("Tried to get error from an OK result");
  }
}

template <typename T, typename E>
void Result<T, E>::serialize(qtils::OArchive &archive) const {
  if (hasValue()) {
    archive << value();
  } else {
    archive << error();
  }
}

}  // namespace aegis

#endif  // AEGIS_RESULT_H
