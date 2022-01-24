#ifndef FLOW_DOCUMENT_H
#define FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
#include <QIcon>
#include <QObject>
#include <QUndoStack>
/* ------------------------------------ Api --------------------------------- */
#include "flow/api/document.h"
/* -------------------------------------------------------------------------- */

class Document : public api::IDocument
{
  Q_OBJECT

public:
  static std::unique_ptr<api::IDocument> load(const QString &file_name, api::IDocumentFormat *format = nullptr, QString *error = nullptr);

public:
  ~Document() override;

  void setFileName(const QString &file_name) override;
  [[nodiscard]] QString getFileName() const override;

  [[nodiscard]] QString getDisplayName() const override;
  [[nodiscard]] QDateTime getLastModified() const override;

  [[nodiscard]] bool isModified() const override;
  [[nodiscard]] QUndoStack *getUndoStack() const override;

  [[nodiscard]] api::IDocumentFormat *getReaderFormat() const override;
  [[nodiscard]] api::IDocumentFormat *getWriterFormat() const override;

  void setReaderFormat(api::IDocumentFormat *format) override;
  void setWriterFormat(api::IDocumentFormat *format) override;

  bool save(const QString &file_name, QString *error) override;

protected:
  explicit Document(Type type, QObject *parent = nullptr);

private:
  QString m_file_name;
  QString m_write_format;
  QString m_read_format;
  QUndoStack *m_undo_stack;
};

#endif//FLOW_DOCUMENT_H
