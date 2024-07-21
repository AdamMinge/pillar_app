#ifndef AEGIS_SERIALIZER_H
#define AEGIS_SERIALIZER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QBuffer>
#include <QMetaType>
#include <QObject>
/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Egnite ------------------------------- */
#include <qtils/serializer/json_archive.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* --------------------------------- Serializer ----------------------------- */

class LIB_AEGIS_API Serializer {
 public:
  enum class Format { Json };

 public:
  explicit Serializer(Format format);
  ~Serializer();

  template <typename Object>
  QByteArray serialize(const Object& object) const;

  template <typename Object>
  Object deserialize(const QByteArray& data) const;

 private:
  Format m_format;
};

template <typename Object>
QByteArray Serializer::serialize(const Object& object) const {
  QByteArray data;
  QBuffer buffer(&data);
  buffer.open(QIODevice::WriteOnly);

  switch (m_format) {
    case Format::Json: {
      qtils::OJsonArchive archive(buffer);
      archive << object;
    }
  }

  return data;
}

template <typename Object>
Object Serializer::deserialize(const QByteArray& data) const {
  Object object;
  QBuffer buffer(&data);
  buffer.open(QIODevice::ReadOnly);

  switch (m_format) {
    case Format::Json: {
      qtils::IJsonArchive archive(buffer);
      archive >> object;
    }
  }

  return object;
}

}  // namespace aegis

#endif  // AEGIS_SERIALIZER_H