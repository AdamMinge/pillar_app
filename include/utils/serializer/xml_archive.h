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
  void saveStart(const QString& name) override;
  void saveEnd(const QString& name) override;

  void arrayStart(qsizetype i) override;
  void arrayEnd(qsizetype i) override;

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
  void loadStart(const QString& name) override;
  void loadEnd(const QString& name) override;

  void arrayStart(qsizetype i) override;
  void arrayEnd(qsizetype i) override;

  QVariant load() override;

 private:
  [[nodiscard]] QStringList getChildNames() const override;
  [[nodiscard]] qsizetype getChildCount() const override;

 private:
  QXmlStreamReader m_reader;
};

}  // namespace utils

#endif  // UTILS_SERIALIZER_XML_SERIALIZER_H
