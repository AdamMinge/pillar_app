/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/document.h"
#include "flow/editor/format_helper.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/api/document_format.h>
/* -------------------------------------------------------------------------- */

Document::Document(Type type, QObject *parent)
    : IDocument(type, parent),
      m_undo_stack(new QUndoStack(this))
{
  connect(m_undo_stack, &QUndoStack::cleanChanged, this, &Document::modifiedChanged);
}

Document::~Document() = default;

void Document::setFileName(const QString &file_name)
{
  if (m_file_name == file_name)
    return;

  auto old_file_name = m_file_name;
  m_file_name = file_name;

  Q_EMIT fileNameChanged(file_name, old_file_name);
}

QString Document::getFileName() const
{
  return m_file_name;
}

QString Document::getDisplayName() const
{
  QString displayName = QFileInfo(m_file_name).fileName();
  if (displayName.isEmpty())
    displayName = tr("untitled");

  return displayName;
}

QDateTime Document::getLastModified() const
{
  return QFileInfo(m_file_name).lastModified();
}

bool Document::isModified() const
{
  return !m_undo_stack->isClean();
}

QUndoStack *Document::getUndoStack() const
{
  return m_undo_stack;
}

api::IDocumentFormat *Document::getReaderFormat() const
{
  return FormatHelper<api::IDocumentFormat>{api::IFileFormat::Capability::Read}.findFormatByShortName(m_read_format);
}

api::IDocumentFormat *Document::getWriterFormat() const
{
  return FormatHelper<api::IDocumentFormat>{api::IFileFormat::Capability::Write}.findFormatByShortName(m_write_format);
}

void Document::setReaderFormat(api::IDocumentFormat *format)
{
  Q_ASSERT(format && format->hasCapabilities(api::IFileFormat::Capability::Read));
  m_read_format = format->getShortName();
}

void Document::setWriterFormat(api::IDocumentFormat *format)
{
  Q_ASSERT(format && format->hasCapabilities(api::IFileFormat::Capability::Write));
  m_write_format = format->getShortName();
}

bool Document::save(const QString &file_name)
{
  auto document_format = getWriterFormat();

  if (!document_format)
    return false;

  if (!document_format->save(*this))
    return false;

  setFileName(file_name);

  Q_EMIT saved();
  return true;
}

std::unique_ptr<api::IDocument> Document::load(const QString &file_name, api::IDocumentFormat *format)
{
  if (!format)
  {
    auto format_helper = FormatHelper<api::IDocumentFormat>{api::IFileFormat::Capability::Read};
    format = format_helper.findFormatByFileName(file_name);
  }

  return format->load(file_name);
}