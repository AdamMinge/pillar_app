#ifndef FLOW_DOCUMENT_H
#define FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
#include <QIcon>
#include <QObject>
#include <QUndoStack>
/* -------------------------------------------------------------------------- */

class DocumentFormat;

class Document : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  static std::unique_ptr<Document> load(const QString &file_name, DocumentFormat *format = nullptr);

public:
  ~Document() override;

  [[nodiscard]] Type getType() const;

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

  bool save(const QString &file_name);

Q_SIGNALS:
  void modifiedChanged();
  void fileNameChanged(const QString &new_file_name, const QString &old_file_name);

  void saved();

protected:
  explicit Document(Type type, QObject *parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
  QString m_write_format;
  QString m_read_format;
  QUndoStack *m_undo_stack;
};

enum class Document::Type
{
  Flow,
  Unknown,
};

#endif//FLOW_DOCUMENT_H
