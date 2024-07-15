#ifndef EGNITE_DOCUMENT_FORMAT_H
#define EGNITE_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
#include "egnite/file_format.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class Document;

class LIB_EGNITE_API DocumentFormat : public FileFormat {
  Q_OBJECT
  Q_INTERFACES(egnite::FileFormat)

 public:
  explicit DocumentFormat(QObject *parent = nullptr);
  ~DocumentFormat() override;

  virtual std::unique_ptr<Document> load(const QString &file_name,
                                         QString *error) = 0;
  virtual bool save(const Document &document, const QString &file_name,
                    QString *error) = 0;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::DocumentFormat, "org.egnite.DocumentFormat")

namespace egnite {

class ReadableDocumentFormat : public DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(egnite::DocumentFormat)

 public:
  explicit ReadableDocumentFormat(QObject *parent = nullptr);
  ~ReadableDocumentFormat() override;

  bool save(const Document &document, const QString &file_name,
            QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableDocumentFormat : public DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(egnite::DocumentFormat)

 public:
  explicit WritableDocumentFormat(QObject *parent = nullptr);
  ~WritableDocumentFormat() override;

  std::unique_ptr<Document> load(const QString &file_name,
                                 QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

}  // namespace egnite

Q_DECLARE_INTERFACE(egnite::ReadableDocumentFormat,
                    "org.egnite.ReadableDocumentFormat")
Q_DECLARE_INTERFACE(egnite::WritableDocumentFormat,
                    "org.egnite.WritableDocumentFormat")

#endif  // EGNITE_DOCUMENT_FORMAT_H
