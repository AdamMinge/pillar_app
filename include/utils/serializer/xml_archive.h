#ifndef UTILS_SERIALIZER_XML_SERIALIZER_H
#define UTILS_SERIALIZER_XML_SERIALIZER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
/* ----------------------------------- Local -------------------------------- */
#include "utils/serializer/archive.h"
#include "utils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

/* -------------------------------- OXmlArchive ----------------------------- */

class SERIALIZER_API OXmlArchive : public OArchive {
 public:
  explicit OXmlArchive(QIODevice& device);
  ~OXmlArchive() override;

 protected:
  void startSave(const QString& name) override;
  void endSave(const QString& name) override;
  void save(const QVariant& value) override;

 private:
  QXmlStreamWriter m_writer;
};

/* -------------------------------- IXmlArchive ----------------------------- */

class SERIALIZER_API IXmlArchive : public IArchive {
 public:
  explicit IXmlArchive(QIODevice& device);
  ~IXmlArchive() override;

 protected:
  void startLoad(const QString& name) override;
  void endLoad(const QString& name) override;
  QVariant load() override;

 private:
  QXmlStreamReader m_reader;
};

}  // namespace utils

#endif  // UTILS_SERIALIZER_XML_SERIALIZER_H
