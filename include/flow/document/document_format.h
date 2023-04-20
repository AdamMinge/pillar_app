#ifndef FLOW_DOCUMENT_FORMAT_H
#define FLOW_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/export.h"
#include "flow/file_format.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Document;

class LIB_FLOW_API DocumentFormat : public FileFormat {
  Q_OBJECT
  Q_INTERFACES(flow::FileFormat)

 public:
  explicit DocumentFormat(QObject *parent = nullptr);
  ~DocumentFormat() override;

  virtual std::unique_ptr<Document> load(const QString &file_name,
                                         QString *error) = 0;
  virtual bool save(const Document &document, const QString &file_name,
                    QString *error) = 0;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::DocumentFormat, "org.flow.DocumentFormat")

namespace flow {

class ReadableDocumentFormat : public DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(flow::DocumentFormat)

 public:
  explicit ReadableDocumentFormat(QObject *parent = nullptr);
  ~ReadableDocumentFormat() override;

  bool save(const Document &document, const QString &file_name,
            QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

class WritableDocumentFormat : public DocumentFormat {
  Q_OBJECT
  Q_INTERFACES(flow::DocumentFormat)

 public:
  explicit WritableDocumentFormat(QObject *parent = nullptr);
  ~WritableDocumentFormat() override;

  std::unique_ptr<Document> load(const QString &file_name,
                                 QString *error) override;
  [[nodiscard]] Capabilities getCapabilities() const override;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::ReadableDocumentFormat,
                    "org.flow.ReadableDocumentFormat")
Q_DECLARE_INTERFACE(flow::WritableDocumentFormat,
                    "org.flow.WritableDocumentFormat")

#endif  // FLOW_DOCUMENT_FORMAT_H
