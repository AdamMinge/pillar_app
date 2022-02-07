#ifndef FLOW_INTERFACE_DOCUMENT_H
#define FLOW_INTERFACE_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
#include <QIcon>
#include <QObject>
#include <QUndoStack>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/export.h"
/* -------------------------------------------------------------------------- */

namespace api::document
{

  class IDocumentFormat;

  class API_API IDocument : public QObject
  {
    Q_OBJECT

  public:
    enum class Type;

  public:
    ~IDocument() override;

    [[nodiscard]] Type getType() const;

    virtual void setFileName(const QString &file_name) = 0;
    [[nodiscard]] virtual QString getFileName() const = 0;

    [[nodiscard]] virtual QString getDisplayName() const = 0;
    [[nodiscard]] virtual QDateTime getLastModified() const = 0;

    [[nodiscard]] virtual bool isModified() const = 0;
    [[nodiscard]] virtual QUndoStack *getUndoStack() const = 0;

    [[nodiscard]] virtual IDocumentFormat *getReaderFormat() const = 0;
    [[nodiscard]] virtual IDocumentFormat *getWriterFormat() const = 0;

    virtual void setReaderFormat(IDocumentFormat *format) = 0;
    virtual void setWriterFormat(IDocumentFormat *format) = 0;

    virtual bool save(const QString &file_name, QString *error) = 0;

  Q_SIGNALS:
    void modifiedChanged();
    void fileNameChanged(const QString &new_file_name,
                         const QString &old_file_name);

    void saved();

  protected:
    explicit IDocument(Type type, QObject *parent = nullptr);

  private:
    Type m_type;
  };

  enum class IDocument::Type
  {
    Flow,
    Unknown,
  };

}// namespace api::document

#endif//FLOW_INTERFACE_DOCUMENT_H
