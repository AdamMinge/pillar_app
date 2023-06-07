#ifndef UTILS_SERIALIZER_ARCHIVE_PROPERTY_H
#define UTILS_SERIALIZER_ARCHIVE_PROPERTY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

template <typename TYPE>
concept IsCreatableAsQVariant = requires(TYPE object) {
  { QVariant(object) } -> std::convertible_to<QVariant>;
};

template <typename TYPE>
class ArchiveProperty {
 public:
  explicit ArchiveProperty(QString name, TYPE& value);
  ~ArchiveProperty();

  QString getName() const;

  TYPE& getValue() const;
  const TYPE& getConstValue() const;

 private:
  QString m_name;
  TYPE* m_value;
};

template <typename TYPE>
ArchiveProperty<TYPE>::ArchiveProperty(QString name, TYPE& value)
    : m_name(std::move(name)), m_value(std::addressof(value)) {}

template <typename TYPE>
ArchiveProperty<TYPE>::~ArchiveProperty() = default;

template <typename TYPE>
QString ArchiveProperty<TYPE>::getName() const {
  return m_name;
}

template <typename TYPE>
TYPE& ArchiveProperty<TYPE>::getValue() const {
  return *m_value;
}

template <typename TYPE>
const TYPE& ArchiveProperty<TYPE>::getConstValue() const {
  return *m_value;
}

}  // namespace utils

#endif  // UTILS_SERIALIZER_ARCHIVE_PROPERTY_H
