#ifndef UTILS_SERIALIZER_ARCHIVE_H
#define UTILS_SERIALIZER_ARCHIVE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/archive_property.h"
#include "utils/serializer/export.h"
#include "utils/serializer/serializable.h"
/* -------------------------------------------------------------------------- */

namespace utils {

/* --------------------------------- OArchive ------------------------------- */

class SERIALIZER_API OArchive {
 public:
  explicit OArchive() = default;
  virtual ~OArchive() = default;

  template <IsSerializable TYPE>
  OArchive& operator<<(const ArchiveProperty<TYPE>& property);

  template <IsCreatableAsQVariant TYPE>
  OArchive& operator<<(const ArchiveProperty<TYPE>& property);

 protected:
  virtual void startSave(const QString& name) = 0;
  virtual void endSave(const QString& name) = 0;
  virtual void save(const QVariant& value) = 0;
};

template <IsSerializable TYPE>
OArchive& OArchive::operator<<(const ArchiveProperty<TYPE>& property) {
  startSave(property.getName());
  property.getConstValue().serialize(*this);
  endSave(property.getName());

  return *this;
}

template <IsCreatableAsQVariant TYPE>
OArchive& OArchive::operator<<(const ArchiveProperty<TYPE>& property) {
  startSave(property.getName());
  save(property.getConstValue());
  endSave(property.getName());

  return *this;
}

/* --------------------------------- IArchive ------------------------------- */

class SERIALIZER_API IArchive {
 public:
  explicit IArchive() = default;
  virtual ~IArchive() = default;

  template <IsDeserializable TYPE>
  IArchive& operator>>(const ArchiveProperty<TYPE>& property);

  template <IsCreatableAsQVariant TYPE>
  IArchive& operator>>(const ArchiveProperty<TYPE>& property);

 protected:
  virtual void startLoad(const QString& name) = 0;
  virtual void endLoad(const QString& name) = 0;
  virtual QVariant load() = 0;
};

template <IsDeserializable TYPE>
IArchive& IArchive::operator>>(const ArchiveProperty<TYPE>& property) {
  startLoad(property.getName());
  property.getValue().deserialize(*this);
  endLoad(property.getName());

  return *this;
}

template <IsCreatableAsQVariant TYPE>
IArchive& IArchive::operator>>(const ArchiveProperty<TYPE>& property) {
  startLoad(property.getName());
  property.getValue() = load().value<TYPE>();
  endLoad(property.getName());
  return *this;
}

}  // namespace utils

#endif  // UTILS_SERIALIZER_ARCHIVE_H
