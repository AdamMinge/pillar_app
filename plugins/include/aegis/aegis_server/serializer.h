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
#include "aegis_server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis_server {

/* ----------------------------- ResponseSerializer ------------------------- */

class LIB_AEGIS_SERVER_API ResponseSerializer {
 public:
  enum class Format { Json };

 public:
  explicit ResponseSerializer(Format format);
  ~ResponseSerializer();

  template <typename Object>
  QByteArray serialize(const Object& object) const;

 private:
  Format m_format;
};

template <typename Object>
QByteArray ResponseSerializer::serialize(const Object& object) const {
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

}  // namespace aegis_server

#endif  // AEGIS_SERIALIZER_H