#ifndef PILLAR_DOCUMENT_FORMAT_H
#define PILLAR_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
#include "pillar/file_format.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class Document;

class LIB_PILLAR_API DocumentFormat : public FileFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::FileFormat)

 public:
  explicit DocumentFormat(QObject *parent = nullptr);
  ~DocumentFormat() override;

  virtual std::unique_ptr<Document> load(const QString &file_name,
                                         QString *error) = 0;
  virtual bool save(const Document &document, const QString &file_name,
                    QString *error) = 0;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::DocumentFormat, "org.pillar.DocumentFormat")

namespace pillar {

class ReadableDocumentFormat : public DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::DocumentFormat)

 public:
  explicit ReadableDocumentFormat(QObject *parent = nullptr);
  ~ReadableDocumentFormat() override;

  bool save(const Document &document, const QString &file_name,
            QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableDocumentFormat : public DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(pillar::DocumentFormat)

 public:
  explicit WritableDocumentFormat(QObject *parent = nullptr);
  ~WritableDocumentFormat() override;

  std::unique_ptr<Document> load(const QString &file_name,
                                 QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

}  // namespace pillar

Q_DECLARE_INTERFACE(pillar::ReadableDocumentFormat,
                    "org.pillar.ReadableDocumentFormat")
Q_DECLARE_INTERFACE(pillar::WritableDocumentFormat,
                    "org.pillar.WritableDocumentFormat")

#endif  // PILLAR_DOCUMENT_FORMAT_H
