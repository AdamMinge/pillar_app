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
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* --------------------------------- Serializer ----------------------------- */

class LIB_AEGIS_SERVER_API Serializer : public QObject {
  Q_OBJECT

 public:
  enum class Format { Json };

 public:
  explicit Serializer(Format format, QObject* parent = nullptr);
  ~Serializer();

  template <typename Object>
  QByteArray serialize(const Object& object) const;

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

}  // namespace aegis

#endif  // AEGIS_SERIALIZER_H