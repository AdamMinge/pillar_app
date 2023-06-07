#ifndef UTILS_SERIALIZER_JSON_SERIALIZER_H
#define UTILS_SERIALIZER_JSON_SERIALIZER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
#include <QJsonDocument>
/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/archive.h"
#include "utils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

/* ------------------------------- OJsonArchive ----------------------------- */

class SERIALIZER_API OJsonArchive : public OArchive {
 public:
  explicit OJsonArchive(QIODevice& device);
  ~OJsonArchive() override;

 protected:
  void startSave(const QString& name) override;
  void endSave(const QString& name) override;
  void save(const QVariant& value) override;

 private:
  QIODevice& m_device;
  QJsonDocument m_json;
};

/* ------------------------------- IJsonArchive ----------------------------- */

class SERIALIZER_API IJsonArchive : public IArchive {
 public:
  explicit IJsonArchive(QIODevice& device);
  ~IJsonArchive() override;

 protected:
  void startLoad(const QString& name) override;
  void endLoad(const QString& name) override;
  QVariant load() override;

 private:
  QIODevice& m_device;
  QJsonDocument m_json;
};

}  // namespace utils

#endif  // UTILS_SERIALIZER_JSON_SERIALIZER_H
