/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/document/document.h"
#include "flow/libflow/document/document_format.h"
#include "flow/libflow/format_helper.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* -------------------------------------------------------------------------- */

namespace flow::document
{

  Document::Document(QString id, QObject *parent)
      : QObject(parent), m_id(std::move(id)), m_undo_stack(new QUndoStack(this))
  {
    connect(
      m_undo_stack, &QUndoStack::cleanChanged, this,
      &Document::modifiedChanged);
  }

  Document::~Document() = default;

  QString Document::getId() const { return m_id; }

  void Document::setFileName(const QString &file_name)
  {
    if (m_file_name == file_name) return;

    auto old_file_name = m_file_name;
    m_file_name = file_name;

    Q_EMIT fileNameChanged(file_name, old_file_name);
  }

  QString Document::getFileName() const { return m_file_name; }

  QString Document::getDisplayName() const
  {
    QString displayName = QFileInfo(m_file_name).fileName();
    if (displayName.isEmpty()) displayName = tr("untitled");

    return displayName;
  }

  QDateTime Document::getLastModified() const
  {
    return QFileInfo(m_file_name).lastModified();
  }

  bool Document::isModified() const { return !m_undo_stack->isClean(); }

  QUndoStack *Document::getUndoStack() const { return m_undo_stack; }

  DocumentFormat *Document::getReaderFormat() const
  {
    return FormatHelper<DocumentFormat>{FileFormat::Capability::Read}
      .findFormatByShortName(m_read_format);
  }

  DocumentFormat *Document::getWriterFormat() const
  {
    return FormatHelper<DocumentFormat>{FileFormat::Capability::Write}
      .findFormatByShortName(m_write_format);
  }

  void Document::setReaderFormat(DocumentFormat *format)
  {
    Q_ASSERT(format && format->hasCapabilities(FileFormat::Capability::Read));
    m_read_format = format->getShortName();
  }

  void Document::setWriterFormat(DocumentFormat *format)
  {
    Q_ASSERT(format && format->hasCapabilities(FileFormat::Capability::Write));
    m_write_format = format->getShortName();
  }

  bool Document::save(const QString &file_name, QString *error)
  {
    auto document_format = getWriterFormat();
    if (!document_format)
    {
      if (error) *error = tr("Wrong document format");
      return false;
    }

    if (!document_format->save(*this, file_name, error)) return false;

    setFileName(file_name);
    m_undo_stack->setClean();

    Q_EMIT saved();
    return true;
  }

  std::unique_ptr<Document> Document::load(
    const QString &file_name, DocumentFormat *format, QString *error)
  {
    if (!format)
    {
      auto format_helper =
        FormatHelper<DocumentFormat>{FileFormat::Capability::Read};
      format = format_helper.findFormatByFileName(file_name);
    }

    if (!format)
    {
      if (error) *error = tr("Wrong document format");
      return nullptr;
    }

    auto document = format->load(file_name, error);
    if (!document) return nullptr;

    document->setFileName(file_name);

    document->setReaderFormat(format);
    if (format->hasCapabilities(FileFormat::Capability::Write))
      document->setWriterFormat(format);

    return document;
  }

}// namespace flow::document
