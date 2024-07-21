#ifndef AEGIS_COMMAND_RESPONSE_H
#define AEGIS_COMMAND_RESPONSE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLatin1String>
#include <QString>
#include <QVariant>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/archive.h>
#include <qtils/serializer/archive_property.h>
#include <qtils/serializer/serializable.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------- ErrorMessage ----------------------------- */

struct LIB_AEGIS_API ErrorMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QString error MEMBER error)
  Q_PROPERTY(QString detail MEMBER detail)

  QString error;
  QString detail;
};

/* ------------------------------- EmptyMessage ----------------------------- */

struct LIB_AEGIS_API EmptyMessage {
  Q_GADGET
};

/* ---------------------------------- Response ------------------------------ */

template <typename T = EmptyMessage, typename E = ErrorMessage>
class Response : public qtils::Serializable, public qtils::Deserializable {
  static constexpr QLatin1String success_status = QLatin1String("success");
  static constexpr QLatin1String error_status = QLatin1String("error");

 public:
  Response(T value);
  Response(E error);

  [[nodiscard]] bool hasValue() const;
  [[nodiscard]] bool hasError() const;

  [[nodiscard]] T value() const;
  [[nodiscard]] E error() const;

  void serialize(qtils::OArchive &archive) const override;
  void deserialize(qtils::IArchive &archive) override;

 private:
  std::variant<T, E> m_body;
};

template <typename T, typename E>
Response<T, E>::Response(T value) : m_body(std::move(value)) {}

template <typename T, typename E>
Response<T, E>::Response(E error) : m_body(std::move(error)) {}

template <typename T, typename E>
bool Response<T, E>::hasValue() const {
  return std::holds_alternative<T>(m_body);
}

template <typename T, typename E>
bool Response<T, E>::hasError() const {
  return std::holds_alternative<E>(m_body);
}

template <typename T, typename E>
T Response<T, E>::value() const {
  if (hasValue()) {
    return std::get<T>(m_body);
  } else {
    throw std::runtime_error("Tried to get value from an error result");
  }
}

template <typename T, typename E>
E Response<T, E>::error() const {
  if (hasError()) {
    return std::get<E>(m_body);
  } else {
    throw std::runtime_error("Tried to get error from an OK result");
  }
}

template <typename T, typename E>
void Response<T, E>::serialize(qtils::OArchive &archive) const {
  if (hasValue()) {
    archive << success_status;
    archive << value();
  } else {
    archive << error_status;
    archive << error();
  }
}

template <typename T, typename E>
void Response<T, E>::deserialize(qtils::IArchive &archive) {
  QString status;
  archive >> status;

  if (status == success_status) {
    T t;
    archive >> t;
    m_body = t;

  } else {
    E e;
    archive >> e;
    m_body = e;
  }
}

}  // namespace aegis

#endif  // AEGIS_COMMAND_RESPONSE_H