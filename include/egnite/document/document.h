#ifndef EGNITE_DOCUMENT_H
#define EGNITE_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
#include <QIcon>
#include <QObject>
#include <QUndoStack>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class DocumentFormat;

class LIB_EGNITE_API Document : public QObject {
  Q_OBJECT

 public:
  static std::unique_ptr<Document> load(const QString &file_name,
                                        DocumentFormat *format = nullptr,
                                        QString *error = nullptr);

 public:
  ~Document() override;

  [[nodiscard]] QString getId() const;

  void setFileName(const QString &file_name);
  [[nodiscard]] QString getFileName() const;

  [[nodiscard]] QString getDisplayName() const;
  [[nodiscard]] QDateTime getLastModified() const;

  [[nodiscard]] bool isModified() const;
  [[nodiscard]] QUndoStack *getUndoStack() const;

  [[nodiscard]] DocumentFormat *getReaderFormat() const;
  [[nodiscard]] DocumentFormat *getWriterFormat() const;

  void setReaderFormat(DocumentFormat *format);
  void setWriterFormat(DocumentFormat *format);

  bool save(const QString &file_name, QString *error);

 Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString &new_file_name,
                       const QString &old_file_name);

  void saved();

 protected:
  explicit Document(QString id, QObject *parent = nullptr);

 private:
  QString m_id;
  QString m_file_name;
  QString m_write_format;
  QString m_read_format;
  QUndoStack *m_undo_stack;
};

}  // namespace egnite

#endif  // EGNITE_DOCUMENT_H
