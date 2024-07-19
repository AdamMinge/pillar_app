#ifndef AEGIS_COMMAND_RESPONSE_H
#define AEGIS_COMMAND_RESPONSE_H

/* ------------------------------------ Qt ---------------------------------- */
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

/* --------------------------------- Response ------------------------------- */

template <typename Type>
class LIB_AEGIS_API Response;

template <>
class LIB_AEGIS_API Response<void> : public qtils::Serializable {
 public:
  QString status() const { return m_status; }
  void setStatus(QString status) { m_status = status; }

  QString message() const { return m_message; }
  void setMessage(QString message) { m_message = message; }

  void serialize(qtils::OArchive &archive) const override {
    archive << qtils::ArchiveProperty("status", m_status);
    archive << qtils::ArchiveProperty("message", m_message);
  }

 protected:
  Response(QString status, QString message)
      : m_status(status), m_message(message) {}

 private:
  QString m_status;
  QString m_message;
};

template <typename Type>
class LIB_AEGIS_API Response : public Response<void> {
 public:
  Type body() const { return m_body.value<Type>(); }
  void setBody(Type body) { m_body = QVariant::fromValue(body); }

  void serialize(qtils::OArchive &archive) const override {
    Response<void>::serialize(archive);
    archive << qtils::ArchiveProperty("body", m_body);
  }

 protected:
  Response(QString status, QString message, Type body)
      : Response<void>(status, message), m_body(QVariant::fromValue(body)) {}

 private:
  QVariant m_body;
};

/* --------------------------------- ErrorBody ------------------------------ */

struct LIB_AEGIS_API ErrorBody {
  Q_GADGET

 public:
  Q_PROPERTY(QString error MEMBER error)

  QString error;
};

/* ------------------------------- ErrorResponse ---------------------------- */

class LIB_AEGIS_API ErrorResponse : public Response<ErrorBody> {
 public:
  ErrorResponse(QString message, QString error)
      : Response<ErrorBody>(QLatin1String("Error"), message, ErrorBody{error}) {
  }
};

/* ------------------------------ SuccessResponse --------------------------- */

template <typename Type>
class LIB_AEGIS_API SuccessResponse : public Response<Type> {
 public:
  SuccessResponse(QString message, Type body)
      : Response<Type>(QLatin1String("Success"), message, body) {}
};

template <>
class LIB_AEGIS_API SuccessResponse<void> : public Response<void> {
 public:
  SuccessResponse(QString message)
      : Response<void>(QLatin1String("Success"), message) {}
};

}  // namespace aegis

#endif  // AEGIS_COMMAND_RESPONSE_H